project('coro', 'cpp')

# Check for `ctx` on the system
ctx_dep = dependency('ctx', required : false)
if not ctx_dep.found()
    # if not present, look for the subproject wrap
    ctx_proj = subproject('ctx')
    # *_dep naming convention to get the dependency
    ctx_dep = ctx_proj.get_variable('ctx_dep')
endif

coro_src = [
    'stack.cpp',
    'coro.cpp'
]

coro_inc = include_directories('.')
coro_lib = static_library('coro', coro_src, include_directories : coro_inc, dependencies : ctx_dep)
coro_dep = declare_dependency(link_with : coro_lib, include_directories : coro_inc, dependencies : ctx_dep)

subdir('test')

executable('coromain', 'main.cpp', dependencies : coro_dep)