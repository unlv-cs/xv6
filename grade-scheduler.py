import re
import subprocess
from gradelib import *


r = Runner(save("xv6.out"))

@test(100, "uscheduler")
def test_uthread():
    r.run_qemu(shell_script([
        'uscheduler'
    ]))
    expected = ['process_a started', 'process_b started', 'process_c started']
    expected.extend(['process_%s %d' % (pid, n) for n in range(100) for pid in ('c', 'a', 'b')])
    expected.extend(['process_c: exit after 100', 'process_a: exit after 100', 'process_b: exit after 100'])
    expected.append('scheduler: no runnable processes')
    if not re.findall('\n'.join(expected), r.qemu.output, re.M):
        raise AssertionError('Output does not match expected output')

run_tests()