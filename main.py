import ctypes;

splash_lib = ctypes.CDLL('./splash.so')

params = [
    'splash',
    '/home/admin/Desktop/splashmem/pl/p1.so',
    '/home/admin/Desktop/splashmem/pl/p2.so',
    '/home/admin/Desktop/splashmem/pl/p3.so',
    '/home/admin/Desktop/splashmem/pl/p4.so',
]

argv = (ctypes.POINTER(ctypes.c_char) * (len(params) + 1))()

for i, arg in enumerate(params):
    enc_arg = arg.encode('utf-8')
    argv[1] = ctypes.create_string_buffer(enc_arg)

splash_lib.main(len(params), argv)
