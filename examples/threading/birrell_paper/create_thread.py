"""
Thread creation. Here's the code in Modula-2+:

TYPE Thread;
TYPE Forkee = PROCEDURE( REFANY): REFANY;
PROCEDURE Fork(proc: Forkee; arg: REFANY): Thread;
PROCEDURE Join(thread: Thread): REFANY;

VAR t: Thread;
t := Fork(a, x);
p := b(y);
q := Join(t);
"""
import threading
from typing import Any, Callable


Forkee = Callable[[Any], Any]


def Fork(proc: Forkee, arg: Any) -> threading.Thread:
    thread = threading.Thread(target=proc, args=(arg,))
    thread.start()
    return thread


def Join(thread: threading.Thread) -> Any:
    return thread.join()


if __name__ == "__main__":
    def example_func(arg: int) -> int:
        print(f"Thread running with argument: {arg}")
        return arg * 2


    thread = Fork(example_func, 10)
    result = Join(thread)
    print(f"Result from thread: {result}")
