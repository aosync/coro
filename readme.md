# coro

Simple C++ stackful coroutine library for use in other projects. Uses [ctx](https://github.com/aosync/ctx) as backend.

## embed in your project

For this, I recommend that you use the meson wrap system. Create a wrap file for coro in `subprojects/`, e.g. to follow head,
```
[wrap-git]
url = git@github.com:aosync/coro
revision = head
```

Then, add these lines in your meson.build file.
```meson
coro_dep = dependency('coro', required : false)
if not coro_dep.found()
    coro_proj = subproject('coro')
    coro_dep = coro_proj.get_variable('coro_proj')
endif
```
You can then add the `coro_dep` dependency to your targets.