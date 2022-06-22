#!/usr/bin/env python

import gdb.types
import gdb

class QueuePrinter(gdb.types.TypePrinter):
    """Une imprimanter pour le type de données `queue_t`, une file de processus"""

    def __init__(self, val):
        """Initialise cette imprimante pour object ou pointer vers une file de processus."""
        self.val = val

    def to_string(self):
        """Imprime une représentation textuelle de la file de processus"""
        buffer = '['

        node = self.val['first']
        while node != 0:
            next = node['next']
            process = node['process']

            buffer += f"P{process['id']}"

            if next != 0:
                buffer += ', '

            node = node['next']

        buffer += ']'

        return buffer

    def display_hint(self):
        """Indique comment les enfants de la file de processus devrait être affiché."""
        return 'array'

    def children(self):
        """Itère sur tous les enfants de la file de processus."""
        node = self.val['first']
        index = 0
        while node != 0:
            yield str(index), node['process']

            node = node['next']
            index += 1

def build_printer(val):
    if str(val.type) in ['queue', 'queue_t', 'queue_t *', 'const queue_t *']:
        return QueuePrinter(val)

    return None

gdb.pretty_printers.append(build_printer)
