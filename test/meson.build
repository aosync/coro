tests = [
    ['stack.cpp', 'Stack allocation and deallocation'],
    ['binding.cpp', 'Binding a context to a lambda'],
    ['calling.cpp', 'Calling a bound context'],
    ['yielding.cpp', 'Yielding correctly from a coroutine'],
    ['yielding_out.cpp', 'Yielding from outside a coroutine fails'],
    ['resuming.cpp', 'Resuming correctly from a coroutine that has yielded'],
    ['autorebind.cpp', 'Automatic rebinding to the initial function when returning'],
    ['rebinding.cpp', 'Rebinding to another function when coroutine is inactive'],
    ['rebinding_active.cpp', 'Rebinding to another function when coroutine is active fails'],
    ['coroception.cpp', 'Resuming a coroutine from within a coroutine'],
    ['resuming_running.cpp', 'Resuming an already running coroutine does nothing']
]

foreach t : tests
    exe = executable(t[0], t[0], dependencies : coro_dep)
    test(t[1], exe)
endforeach