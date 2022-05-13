project('HStar', 'c',
  version : '0.1.0',
  license : 'MIT',
  default_options : ['c_std=c11',
                     'warning_level=3'])

hstar_src = [
  'src/main.c',
  'src/node.c',
  'src/astar.c'
]

hstar_inc = [
  'include'
]

cc = meson.get_compiler('c')

glib_dep = dependency('glib-2.0')
m_dep = cc.find_library('m', required : false)

hstar_exe = executable('hstar', hstar_src,
  dependencies : [glib_dep, m_dep],
  include_directories : hstar_inc,
  install : true)

test('hstar', hstar_exe)

