#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>

#include "error.h"
#include "process.h"
#include "scheduler.h"
#include "statistics.h"

#define warn(fmt, ...) \
    do \
    { \
        fprintf(stderr, "[%s:%u] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    } while (false)

#define error(fmt, ...) \
    do \
    { \
        warn(fmt, ##__VA_ARGS__); \
        exit(EXIT_FAILURE); \
    } while (false)

struct {
    const char*         file;
    scheduler_type_t    scheduler_type;
    bool                trace;
} options = {
    .file               = NULL,
    .scheduler_type     = FCFS_SCHEDULER,
    .trace              = false
};

static void parse_options(int argc, char** argv);

int main(int argc, char** argv)
{
    parse_options(argc, argv);

    error_t err;

    FILE* file = fopen(options.file, "r");
    if (file == NULL)
    {
        error("failed to open the \"%s\" file", options.file);
    }

    size_t processes_length = 0;
    size_t processes_capacity = 32;
    process_t* processes = malloc(sizeof(*processes) * processes_capacity);
    if (processes == NULL)
    {
        fclose(file);
        error("failed to allocate a list of processes");
    }

    char* line = NULL;
    size_t line_len = 0;

    while (getline(&line, &line_len, file) != -1)
    {
        if (processes_length >= processes_capacity)
        {
            processes_capacity *= 2;
            processes = realloc(processes, sizeof(*processes) * processes_capacity);
            if (processes == NULL)
            {
                fclose(file);
                error("failed to reallocate the processes");
            }
        }

        process_t* process = &processes[processes_length++];
        process_init_from_line(process, line, processes_length);

        line = NULL;
        line_len = 0;
    }

    fclose(file);

    scheduler_t scheduler;
    if ((err = scheduler_init(&scheduler, options.scheduler_type)) != OK)
    {
        error("failed to initialize the scheduler: %s", error_to_str(err));
    }

    size_t current_tick = 0;
    size_t scheduled_processes_count = 0;
    while (scheduler_has_work(&scheduler) || scheduled_processes_count < processes_length)
    {
        for (process_t* process = processes; process < processes + processes_length; ++process)
        {
            if (process->arrival_time == current_tick)
            {
                process_set_ready(process);

                err = scheduler_schedule(&scheduler, process);
                if (err != 0)
                {
                    scheduler_deinit(&scheduler);
                    free(processes);
                    error("failed to schedule process %zu at tick %zu: %s", process->pid, current_tick, error_to_str(err));
                }

                scheduled_processes_count++;
            }
        }

        if (options.trace)
        {
            printf("TICK: %zu\n", current_tick);
            scheduler_trace(&scheduler);
        }

        if ((err = scheduler_tick(&scheduler)) != 0)
        {
            scheduler_deinit(&scheduler);
            free(processes);
            error("failed to tick the scheduler at tick %zu: %s", current_tick, error_to_str(err));
        }

        current_tick++;

        for (process_t* process = processes; process < processes + processes_length; ++process)
        {
            process_tick(process);
        }
    }

    scheduler_deinit(&scheduler);

    double real_average_wait_time = 0;
    size_t real_processes_count = 0;
    double user_average_wait_time = 0;
    size_t user_processes_count = 0;
    double average_wait_time = 0;
    size_t processes_count = 0;

    for (process_t* process = processes; process < processes + processes_length; ++process)
    {
        switch (process->type)
        {
        case REAL:
            real_processes_count++;
            real_average_wait_time = cummulative_average(real_average_wait_time, (double) process->waited_time, real_processes_count);
            break;
        case USER:
            user_processes_count++;
            user_average_wait_time = cummulative_average(user_average_wait_time, (double) process->waited_time, user_processes_count);
            break;
        }

        processes_count++;
        average_wait_time = cummulative_average(average_wait_time, (double) process->waited_time, processes_count);
    }

    free(processes);

    printf("Real Average Wait Time: %f seconds for %zu processes\n", real_average_wait_time, real_processes_count);
    printf("User Average Wait Time: %f seconds for %zu processes\n", user_average_wait_time, user_processes_count);
    printf("Average Wait Time: %f seconds for %zu processes\n", average_wait_time, processes_count);

    return EXIT_SUCCESS;
}

static void parse_options(int argc, char** argv)
{
    static const char* SHORTOPTS = ":f:s:th";
    static const struct option LONGOPTS[] = {
        {"file",        required_argument,  NULL,   'f'},
        {"scheduler",   required_argument,  NULL,   's'},
        {"trace",       no_argument,        NULL,   't'},
        {"help",        no_argument,        NULL,   'h'},
        {NULL,          0,                  NULL,   0}
    };

    typedef struct string_to_scheduler_type {
        const char*         string;
        scheduler_type_t    scheduler_type;
    } string_to_scheduler_type_t;

    static const string_to_scheduler_type_t SCHEDULERS[] = {
        {"fcfs",        FCFS_SCHEDULER},
        {"priority",    PRIORITY_SCHEDULER},
        {"hybrid",      HYBRID_SCHEDULER},
        {"f",           FCFS_SCHEDULER},
        {"p",           PRIORITY_SCHEDULER},
        {"h",           HYBRID_SCHEDULER},
        {NULL,          0}
    };

    const string_to_scheduler_type_t* string_to_scheduler_type_it = SCHEDULERS;

    bool usage = false;

    while (true)
    {
        int c = getopt_long(argc, argv, SHORTOPTS, LONGOPTS, NULL);

        if (c == -1)
        {
            break;
        }

        switch (c)
        {
        case 'f':
            options.file = optarg;

            break;
        case 's':
            while (string_to_scheduler_type_it->string != NULL)
            {
                if (strcasecmp(string_to_scheduler_type_it->string, optarg) == 0)
                {
                    break;
                }

                string_to_scheduler_type_it++;
            }

            if (string_to_scheduler_type_it->string == NULL)
            {
                usage = true;
            }
            else
            {
                options.scheduler_type = string_to_scheduler_type_it->scheduler_type;
            }

            break;
        case 't':
            options.trace = true;

            break;
        case 'h':
            usage = true;

            break;
        case '?':
            usage = true;

            break;
        case ':':
            usage = true;

            break;
        default:
            warn("getopt_long returned an unknown character code: %c", c);
            exit(EXIT_FAILURE);
            return;
        }
    }

    if (usage || options.file == NULL)
    {
        printf(
            "UTILISATION:\n"
            "\n"
            "\t%s --file file [--scheduler fcfs|priority|hybrid] [--trace] [--help]\n"
            "\n"
            "DESCRIPTION:\n"
            "\n"
            "\tLance la simulation d'une stratégie d'ordonnancement.\n"
            "\n"
            "OPTIONS:\n"
            "\n"
            "\t--file <file>\n"
            "\t\tIndique à la simulation quel fichier d'entrées de processus à utiliser\n"
            "\n"
            "\t--scheduler fcfs|priority|hybrid\n"
            "\t\tIndique à la simulation le type d'ordonnanceur à utiliser.\n"
            "\t\tLa valeur par défaut est \"fcfs\".\n"
            "\n"
            "\t--trace\n"
            "\t\tActive le mode *trace*. À chaque *tick*, l'état de l'ordonnanceur sera imprimmé dans la sortie standard.\n"
            "\n"
            "\t--help\n"
            "\t\tAffiche ce message d'erreur.\n",
            argv[0]
        );
        exit(EXIT_FAILURE);
    }
}
