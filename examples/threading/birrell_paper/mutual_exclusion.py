"""
Mutual exclusion. Here's the code in Modula-2+:

TYPE List = REF RECORD ch: CHAR; next: List END;
VAR m: Thread.Mutex;
VAR head: List;

LOCK m DO
    newElement^.next := head;
    head := newElement;
END;
"""
import threading


class ListNode:
    def __init__(self, ch, next_node=None) -> None:
        self.ch = ch    # character data
        self.next = next_node # ref to the next node in the list

# create a lock (equivalent to the Mutex in Modula-2+)
m = threading.Lock()

# head of the linked list
head = None


def add_to_list(new_element):
    global head
    with m:
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
    new_element = ListNode('a')
    add_to_list(new_element)

    new_element2 = ListNode('b')
    add_to_list(new_element2)

    new_element3 = ListNode('c')
    add_to_list(new_element3)