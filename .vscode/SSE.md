| Instruction | Opcode/Instruction                    | Source                                                                     |
| ----------- | ------------------------------------- | -------------------------------------------------------------------------- |
| psrldq      | 66 0F 73 /3 ib PSRLDQ xmm1, imm8      | https://www.felixcloutier.com/x86/psrldq                                   |
| punpckhbw   | 66 0F 68 /r PUNPCKHBW xmm1, xmm2/m128 | https://www.felixcloutier.com/x86/punpckhbw:punpckhwd:punpckhdq:punpckhqdq |
| punpcklwd   | 66 0F 61 /r PUNPCKLWD xmm1, xmm2/m128 | https://www.felixcloutier.com/x86/punpcklbw:punpcklwd:punpckldq:punpcklqdq |
| punpckhwd   | 66 0F 69 /r PUNPCKHWD xmm1, xmm2/m128 | https://www.felixcloutier.com/x86/punpckhbw:punpckhwd:punpckhdq:punpckhqdq |
| pmaddwd     | 66 0F F5 /r PMADDWD xmm1, xmm2/m128   | https://www.felixcloutier.com/x86/pmaddwd                                  |
| packssdw    | 66 0F 6B /r PACKSSDW xmm1, xmm2/m128  | https://www.felixcloutier.com/x86/packsswb:packssdw                        |
| psllw       | 66 0F 71 /6 ib PSLLW xmm1, imm8       | https://www.felixcloutier.com/x86/psllw:pslld:psllq                        |