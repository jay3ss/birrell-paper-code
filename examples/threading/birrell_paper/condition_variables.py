"""Condition variables. Here's the code in Modula-2+:

TYPE Condition;
PROCEDURE Wait(m: Mutex; c: Condition);
PROCEDURE Signal(c: Condition);
PROCEDURE Broadcast(c: Condition);
VAR nonEmpty: Thread.Condition;

LOCK m DO
    WHILE head = NIL DO Thread.Wait(m, nonEmpty) END;
    topElement := head;
    head := head^.next;
    Thread.Signal(nonEmpty)
END;

NOTE: this example will run, but it hangs because nothing is being added
to the list's head.
"""
import threading


class ListNode:
    def __init__(self, ch, next_node=None) -> None:
        self.ch = ch    # character data
        self.next = next_node # ref to the next node in the list


# types
Mutex = threading.Lock
Condition = threading.Condition

# create a lock (equivalent to the Mutex in Modula-2+)
mutex = Mutex()

non_empty = Condition(mutex)

# head of the linked list
head = None

def wait(mutex: Mutex, condition: Condition) -> None:
    while head is None:
        condition.wait()

def signal(condition: Condition) -> None:
    condition.notify()


def add_to_list(new_element):
    global head
    with mutex:
        print(f"Adding element '{new_element.ch}' to the list.")
        new_element.next = head
        head = new_element
        print_current_list()


# Function to print the current state of the list
def print_current_list():
    global head
    current = head
    elements = []
    while current:
        elements.append(current.ch)
        current = current.next
    print("Current list:", " -> ".join(elements))


if __name__ == "__main__":
    with mutex:
        wait(mutex, non_empty)

        top_element = head
        head = head.next
        non_empty.notify()