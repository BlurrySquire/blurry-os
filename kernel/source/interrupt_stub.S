.section .text
interrupt_stub:
    push %rax
    push %rbx
    push %rcx
    push %rdx
    push %rsi
    push %rdi
    push %rbp
    push %r8
    push %r9
    push %r10
    push %r11
    push %r12
    push %r13
    push %r14
    push %r15

    call interrupt_handler

    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %r11
    pop %r10
    pop %r9
    pop %r8
    pop %rbp
    pop %rdi
    pop %rsi
    pop %rdx
    pop %rcx
    pop %rbx
    pop %rax

    add $16, %rsp

    iretq

.align 16
.global vector_0_handler
vector_0_handler:
	pushq $0
	pushq $0
	jmp interrupt_stub

.align 16
vector_1_handler:
	pushq $0
	pushq $1
	jmp interrupt_stub

.align 16
vector_2_handler:
	pushq $0
	pushq $2
	jmp interrupt_stub

.align 16
vector_3_handler:
	pushq $0
	pushq $3
	jmp interrupt_stub

.align 16
vector_4_handler:
	pushq $0
	pushq $4
	jmp interrupt_stub

.align 16
vector_5_handler:
	pushq $0
	pushq $5
	jmp interrupt_stub

.align 16
vector_6_handler:
	pushq $0
	pushq $6
	jmp interrupt_stub

.align 16
vector_7_handler:
	pushq $0
	pushq $7
	jmp interrupt_stub

.align 16
vector_8_handler:
	pushq $8
	jmp interrupt_stub

.align 16
vector_9_handler:
	pushq $0
	pushq $9
	jmp interrupt_stub

.align 16
vector_10_handler:
	pushq $10
	jmp interrupt_stub

.align 16
vector_11_handler:
	pushq $11
	jmp interrupt_stub

.align 16
vector_12_handler:
	pushq $12
	jmp interrupt_stub

.align 16
vector_13_handler:
	pushq $13
	jmp interrupt_stub

.align 16
vector_14_handler:
	pushq $14
	jmp interrupt_stub

.align 16
vector_15_handler:
	pushq $0
	pushq $15
	jmp interrupt_stub

.align 16
vector_16_handler:
	pushq $0
	pushq $16
	jmp interrupt_stub

.align 16
vector_17_handler:
	pushq $17
	jmp interrupt_stub

.align 16
vector_18_handler:
	pushq $0
	pushq $18
	jmp interrupt_stub

.align 16
vector_19_handler:
	pushq $0
	pushq $19
	jmp interrupt_stub

.align 16
vector_20_handler:
	pushq $0
	pushq $20
	jmp interrupt_stub

.align 16
vector_21_handler:
	pushq $21
	jmp interrupt_stub

.align 16
vector_22_handler:
	pushq $0
	pushq $22
	jmp interrupt_stub

.align 16
vector_23_handler:
	pushq $0
	pushq $23
	jmp interrupt_stub

.align 16
vector_24_handler:
	pushq $0
	pushq $24
	jmp interrupt_stub

.align 16
vector_25_handler:
	pushq $0
	pushq $25
	jmp interrupt_stub

.align 16
vector_26_handler:
	pushq $0
	pushq $26
	jmp interrupt_stub

.align 16
vector_27_handler:
	pushq $0
	pushq $27
	jmp interrupt_stub

.align 16
vector_28_handler:
	pushq $0
	pushq $28
	jmp interrupt_stub

.align 16
vector_29_handler:
	pushq $0
	pushq $29
	jmp interrupt_stub

.align 16
vector_30_handler:
	pushq $0
	pushq $30
	jmp interrupt_stub

.align 16
vector_31_handler:
	pushq $0
	pushq $31
	jmp interrupt_stub

.align 16
vector_32_handler:
	pushq $0
	pushq $32
	jmp interrupt_stub

.align 16
vector_33_handler:
	pushq $0
	pushq $33
	jmp interrupt_stub

.align 16
vector_34_handler:
	pushq $0
	pushq $34
	jmp interrupt_stub

.align 16
vector_35_handler:
	pushq $0
	pushq $35
	jmp interrupt_stub

.align 16
vector_36_handler:
	pushq $0
	pushq $36
	jmp interrupt_stub

.align 16
vector_37_handler:
	pushq $0
	pushq $37
	jmp interrupt_stub

.align 16
vector_38_handler:
	pushq $0
	pushq $38
	jmp interrupt_stub

.align 16
vector_39_handler:
	pushq $0
	pushq $39
	jmp interrupt_stub

.align 16
vector_40_handler:
	pushq $0
	pushq $40
	jmp interrupt_stub

.align 16
vector_41_handler:
	pushq $0
	pushq $41
	jmp interrupt_stub

.align 16
vector_42_handler:
	pushq $0
	pushq $42
	jmp interrupt_stub

.align 16
vector_43_handler:
	pushq $0
	pushq $43
	jmp interrupt_stub

.align 16
vector_44_handler:
	pushq $0
	pushq $44
	jmp interrupt_stub

.align 16
vector_45_handler:
	pushq $0
	pushq $45
	jmp interrupt_stub

.align 16
vector_46_handler:
	pushq $0
	pushq $46
	jmp interrupt_stub

.align 16
vector_47_handler:
	pushq $0
	pushq $47
	jmp interrupt_stub

.align 16
vector_48_handler:
	pushq $0
	pushq $48
	jmp interrupt_stub

.align 16
vector_49_handler:
	pushq $0
	pushq $49
	jmp interrupt_stub

.align 16
vector_50_handler:
	pushq $0
	pushq $50
	jmp interrupt_stub

.align 16
vector_51_handler:
	pushq $0
	pushq $51
	jmp interrupt_stub

.align 16
vector_52_handler:
	pushq $0
	pushq $52
	jmp interrupt_stub

.align 16
vector_53_handler:
	pushq $0
	pushq $53
	jmp interrupt_stub

.align 16
vector_54_handler:
	pushq $0
	pushq $54
	jmp interrupt_stub

.align 16
vector_55_handler:
	pushq $0
	pushq $55
	jmp interrupt_stub

.align 16
vector_56_handler:
	pushq $0
	pushq $56
	jmp interrupt_stub

.align 16
vector_57_handler:
	pushq $0
	pushq $57
	jmp interrupt_stub

.align 16
vector_58_handler:
	pushq $0
	pushq $58
	jmp interrupt_stub

.align 16
vector_59_handler:
	pushq $0
	pushq $59
	jmp interrupt_stub

.align 16
vector_60_handler:
	pushq $0
	pushq $60
	jmp interrupt_stub

.align 16
vector_61_handler:
	pushq $0
	pushq $61
	jmp interrupt_stub

.align 16
vector_62_handler:
	pushq $0
	pushq $62
	jmp interrupt_stub

.align 16
vector_63_handler:
	pushq $0
	pushq $63
	jmp interrupt_stub

.align 16
vector_64_handler:
	pushq $0
	pushq $64
	jmp interrupt_stub

.align 16
vector_65_handler:
	pushq $0
	pushq $65
	jmp interrupt_stub

.align 16
vector_66_handler:
	pushq $0
	pushq $66
	jmp interrupt_stub

.align 16
vector_67_handler:
	pushq $0
	pushq $67
	jmp interrupt_stub

.align 16
vector_68_handler:
	pushq $0
	pushq $68
	jmp interrupt_stub

.align 16
vector_69_handler:
	pushq $0
	pushq $69
	jmp interrupt_stub

.align 16
vector_70_handler:
	pushq $0
	pushq $70
	jmp interrupt_stub

.align 16
vector_71_handler:
	pushq $0
	pushq $71
	jmp interrupt_stub

.align 16
vector_72_handler:
	pushq $0
	pushq $72
	jmp interrupt_stub

.align 16
vector_73_handler:
	pushq $0
	pushq $73
	jmp interrupt_stub

.align 16
vector_74_handler:
	pushq $0
	pushq $74
	jmp interrupt_stub

.align 16
vector_75_handler:
	pushq $0
	pushq $75
	jmp interrupt_stub

.align 16
vector_76_handler:
	pushq $0
	pushq $76
	jmp interrupt_stub

.align 16
vector_77_handler:
	pushq $0
	pushq $77
	jmp interrupt_stub

.align 16
vector_78_handler:
	pushq $0
	pushq $78
	jmp interrupt_stub

.align 16
vector_79_handler:
	pushq $0
	pushq $79
	jmp interrupt_stub

.align 16
vector_80_handler:
	pushq $0
	pushq $80
	jmp interrupt_stub

.align 16
vector_81_handler:
	pushq $0
	pushq $81
	jmp interrupt_stub

.align 16
vector_82_handler:
	pushq $0
	pushq $82
	jmp interrupt_stub

.align 16
vector_83_handler:
	pushq $0
	pushq $83
	jmp interrupt_stub

.align 16
vector_84_handler:
	pushq $0
	pushq $84
	jmp interrupt_stub

.align 16
vector_85_handler:
	pushq $0
	pushq $85
	jmp interrupt_stub

.align 16
vector_86_handler:
	pushq $0
	pushq $86
	jmp interrupt_stub

.align 16
vector_87_handler:
	pushq $0
	pushq $87
	jmp interrupt_stub

.align 16
vector_88_handler:
	pushq $0
	pushq $88
	jmp interrupt_stub

.align 16
vector_89_handler:
	pushq $0
	pushq $89
	jmp interrupt_stub

.align 16
vector_90_handler:
	pushq $0
	pushq $90
	jmp interrupt_stub

.align 16
vector_91_handler:
	pushq $0
	pushq $91
	jmp interrupt_stub

.align 16
vector_92_handler:
	pushq $0
	pushq $92
	jmp interrupt_stub

.align 16
vector_93_handler:
	pushq $0
	pushq $93
	jmp interrupt_stub

.align 16
vector_94_handler:
	pushq $0
	pushq $94
	jmp interrupt_stub

.align 16
vector_95_handler:
	pushq $0
	pushq $95
	jmp interrupt_stub

.align 16
vector_96_handler:
	pushq $0
	pushq $96
	jmp interrupt_stub

.align 16
vector_97_handler:
	pushq $0
	pushq $97
	jmp interrupt_stub

.align 16
vector_98_handler:
	pushq $0
	pushq $98
	jmp interrupt_stub

.align 16
vector_99_handler:
	pushq $0
	pushq $99
	jmp interrupt_stub

.align 16
vector_100_handler:
	pushq $0
	pushq $100
	jmp interrupt_stub

.align 16
vector_101_handler:
	pushq $0
	pushq $101
	jmp interrupt_stub

.align 16
vector_102_handler:
	pushq $0
	pushq $102
	jmp interrupt_stub

.align 16
vector_103_handler:
	pushq $0
	pushq $103
	jmp interrupt_stub

.align 16
vector_104_handler:
	pushq $0
	pushq $104
	jmp interrupt_stub

.align 16
vector_105_handler:
	pushq $0
	pushq $105
	jmp interrupt_stub

.align 16
vector_106_handler:
	pushq $0
	pushq $106
	jmp interrupt_stub

.align 16
vector_107_handler:
	pushq $0
	pushq $107
	jmp interrupt_stub

.align 16
vector_108_handler:
	pushq $0
	pushq $108
	jmp interrupt_stub

.align 16
vector_109_handler:
	pushq $0
	pushq $109
	jmp interrupt_stub

.align 16
vector_110_handler:
	pushq $0
	pushq $110
	jmp interrupt_stub

.align 16
vector_111_handler:
	pushq $0
	pushq $111
	jmp interrupt_stub

.align 16
vector_112_handler:
	pushq $0
	pushq $112
	jmp interrupt_stub

.align 16
vector_113_handler:
	pushq $0
	pushq $113
	jmp interrupt_stub

.align 16
vector_114_handler:
	pushq $0
	pushq $114
	jmp interrupt_stub

.align 16
vector_115_handler:
	pushq $0
	pushq $115
	jmp interrupt_stub

.align 16
vector_116_handler:
	pushq $0
	pushq $116
	jmp interrupt_stub

.align 16
vector_117_handler:
	pushq $0
	pushq $117
	jmp interrupt_stub

.align 16
vector_118_handler:
	pushq $0
	pushq $118
	jmp interrupt_stub

.align 16
vector_119_handler:
	pushq $0
	pushq $119
	jmp interrupt_stub

.align 16
vector_120_handler:
	pushq $0
	pushq $120
	jmp interrupt_stub

.align 16
vector_121_handler:
	pushq $0
	pushq $121
	jmp interrupt_stub

.align 16
vector_122_handler:
	pushq $0
	pushq $122
	jmp interrupt_stub

.align 16
vector_123_handler:
	pushq $0
	pushq $123
	jmp interrupt_stub

.align 16
vector_124_handler:
	pushq $0
	pushq $124
	jmp interrupt_stub

.align 16
vector_125_handler:
	pushq $0
	pushq $125
	jmp interrupt_stub

.align 16
vector_126_handler:
	pushq $0
	pushq $126
	jmp interrupt_stub

.align 16
vector_127_handler:
	pushq $0
	pushq $127
	jmp interrupt_stub

.align 16
vector_128_handler:
	pushq $0
	pushq $128
	jmp interrupt_stub

.align 16
vector_129_handler:
	pushq $0
	pushq $129
	jmp interrupt_stub

.align 16
vector_130_handler:
	pushq $0
	pushq $130
	jmp interrupt_stub

.align 16
vector_131_handler:
	pushq $0
	pushq $131
	jmp interrupt_stub

.align 16
vector_132_handler:
	pushq $0
	pushq $132
	jmp interrupt_stub

.align 16
vector_133_handler:
	pushq $0
	pushq $133
	jmp interrupt_stub

.align 16
vector_134_handler:
	pushq $0
	pushq $134
	jmp interrupt_stub

.align 16
vector_135_handler:
	pushq $0
	pushq $135
	jmp interrupt_stub

.align 16
vector_136_handler:
	pushq $0
	pushq $136
	jmp interrupt_stub

.align 16
vector_137_handler:
	pushq $0
	pushq $137
	jmp interrupt_stub

.align 16
vector_138_handler:
	pushq $0
	pushq $138
	jmp interrupt_stub

.align 16
vector_139_handler:
	pushq $0
	pushq $139
	jmp interrupt_stub

.align 16
vector_140_handler:
	pushq $0
	pushq $140
	jmp interrupt_stub

.align 16
vector_141_handler:
	pushq $0
	pushq $141
	jmp interrupt_stub

.align 16
vector_142_handler:
	pushq $0
	pushq $142
	jmp interrupt_stub

.align 16
vector_143_handler:
	pushq $0
	pushq $143
	jmp interrupt_stub

.align 16
vector_144_handler:
	pushq $0
	pushq $144
	jmp interrupt_stub

.align 16
vector_145_handler:
	pushq $0
	pushq $145
	jmp interrupt_stub

.align 16
vector_146_handler:
	pushq $0
	pushq $146
	jmp interrupt_stub

.align 16
vector_147_handler:
	pushq $0
	pushq $147
	jmp interrupt_stub

.align 16
vector_148_handler:
	pushq $0
	pushq $148
	jmp interrupt_stub

.align 16
vector_149_handler:
	pushq $0
	pushq $149
	jmp interrupt_stub

.align 16
vector_150_handler:
	pushq $0
	pushq $150
	jmp interrupt_stub

.align 16
vector_151_handler:
	pushq $0
	pushq $151
	jmp interrupt_stub

.align 16
vector_152_handler:
	pushq $0
	pushq $152
	jmp interrupt_stub

.align 16
vector_153_handler:
	pushq $0
	pushq $153
	jmp interrupt_stub

.align 16
vector_154_handler:
	pushq $0
	pushq $154
	jmp interrupt_stub

.align 16
vector_155_handler:
	pushq $0
	pushq $155
	jmp interrupt_stub

.align 16
vector_156_handler:
	pushq $0
	pushq $156
	jmp interrupt_stub

.align 16
vector_157_handler:
	pushq $0
	pushq $157
	jmp interrupt_stub

.align 16
vector_158_handler:
	pushq $0
	pushq $158
	jmp interrupt_stub

.align 16
vector_159_handler:
	pushq $0
	pushq $159
	jmp interrupt_stub

.align 16
vector_160_handler:
	pushq $0
	pushq $160
	jmp interrupt_stub

.align 16
vector_161_handler:
	pushq $0
	pushq $161
	jmp interrupt_stub

.align 16
vector_162_handler:
	pushq $0
	pushq $162
	jmp interrupt_stub

.align 16
vector_163_handler:
	pushq $0
	pushq $163
	jmp interrupt_stub

.align 16
vector_164_handler:
	pushq $0
	pushq $164
	jmp interrupt_stub

.align 16
vector_165_handler:
	pushq $0
	pushq $165
	jmp interrupt_stub

.align 16
vector_166_handler:
	pushq $0
	pushq $166
	jmp interrupt_stub

.align 16
vector_167_handler:
	pushq $0
	pushq $167
	jmp interrupt_stub

.align 16
vector_168_handler:
	pushq $0
	pushq $168
	jmp interrupt_stub

.align 16
vector_169_handler:
	pushq $0
	pushq $169
	jmp interrupt_stub

.align 16
vector_170_handler:
	pushq $0
	pushq $170
	jmp interrupt_stub

.align 16
vector_171_handler:
	pushq $0
	pushq $171
	jmp interrupt_stub

.align 16
vector_172_handler:
	pushq $0
	pushq $172
	jmp interrupt_stub

.align 16
vector_173_handler:
	pushq $0
	pushq $173
	jmp interrupt_stub

.align 16
vector_174_handler:
	pushq $0
	pushq $174
	jmp interrupt_stub

.align 16
vector_175_handler:
	pushq $0
	pushq $175
	jmp interrupt_stub

.align 16
vector_176_handler:
	pushq $0
	pushq $176
	jmp interrupt_stub

.align 16
vector_177_handler:
	pushq $0
	pushq $177
	jmp interrupt_stub

.align 16
vector_178_handler:
	pushq $0
	pushq $178
	jmp interrupt_stub

.align 16
vector_179_handler:
	pushq $0
	pushq $179
	jmp interrupt_stub

.align 16
vector_180_handler:
	pushq $0
	pushq $180
	jmp interrupt_stub

.align 16
vector_181_handler:
	pushq $0
	pushq $181
	jmp interrupt_stub

.align 16
vector_182_handler:
	pushq $0
	pushq $182
	jmp interrupt_stub

.align 16
vector_183_handler:
	pushq $0
	pushq $183
	jmp interrupt_stub

.align 16
vector_184_handler:
	pushq $0
	pushq $184
	jmp interrupt_stub

.align 16
vector_185_handler:
	pushq $0
	pushq $185
	jmp interrupt_stub

.align 16
vector_186_handler:
	pushq $0
	pushq $186
	jmp interrupt_stub

.align 16
vector_187_handler:
	pushq $0
	pushq $187
	jmp interrupt_stub

.align 16
vector_188_handler:
	pushq $0
	pushq $188
	jmp interrupt_stub

.align 16
vector_189_handler:
	pushq $0
	pushq $189
	jmp interrupt_stub

.align 16
vector_190_handler:
	pushq $0
	pushq $190
	jmp interrupt_stub

.align 16
vector_191_handler:
	pushq $0
	pushq $191
	jmp interrupt_stub

.align 16
vector_192_handler:
	pushq $0
	pushq $192
	jmp interrupt_stub

.align 16
vector_193_handler:
	pushq $0
	pushq $193
	jmp interrupt_stub

.align 16
vector_194_handler:
	pushq $0
	pushq $194
	jmp interrupt_stub

.align 16
vector_195_handler:
	pushq $0
	pushq $195
	jmp interrupt_stub

.align 16
vector_196_handler:
	pushq $0
	pushq $196
	jmp interrupt_stub

.align 16
vector_197_handler:
	pushq $0
	pushq $197
	jmp interrupt_stub

.align 16
vector_198_handler:
	pushq $0
	pushq $198
	jmp interrupt_stub

.align 16
vector_199_handler:
	pushq $0
	pushq $199
	jmp interrupt_stub

.align 16
vector_200_handler:
	pushq $0
	pushq $200
	jmp interrupt_stub

.align 16
vector_201_handler:
	pushq $0
	pushq $201
	jmp interrupt_stub

.align 16
vector_202_handler:
	pushq $0
	pushq $202
	jmp interrupt_stub

.align 16
vector_203_handler:
	pushq $0
	pushq $203
	jmp interrupt_stub

.align 16
vector_204_handler:
	pushq $0
	pushq $204
	jmp interrupt_stub

.align 16
vector_205_handler:
	pushq $0
	pushq $205
	jmp interrupt_stub

.align 16
vector_206_handler:
	pushq $0
	pushq $206
	jmp interrupt_stub

.align 16
vector_207_handler:
	pushq $0
	pushq $207
	jmp interrupt_stub

.align 16
vector_208_handler:
	pushq $0
	pushq $208
	jmp interrupt_stub

.align 16
vector_209_handler:
	pushq $0
	pushq $209
	jmp interrupt_stub

.align 16
vector_210_handler:
	pushq $0
	pushq $210
	jmp interrupt_stub

.align 16
vector_211_handler:
	pushq $0
	pushq $211
	jmp interrupt_stub

.align 16
vector_212_handler:
	pushq $0
	pushq $212
	jmp interrupt_stub

.align 16
vector_213_handler:
	pushq $0
	pushq $213
	jmp interrupt_stub

.align 16
vector_214_handler:
	pushq $0
	pushq $214
	jmp interrupt_stub

.align 16
vector_215_handler:
	pushq $0
	pushq $215
	jmp interrupt_stub

.align 16
vector_216_handler:
	pushq $0
	pushq $216
	jmp interrupt_stub

.align 16
vector_217_handler:
	pushq $0
	pushq $217
	jmp interrupt_stub

.align 16
vector_218_handler:
	pushq $0
	pushq $218
	jmp interrupt_stub

.align 16
vector_219_handler:
	pushq $0
	pushq $219
	jmp interrupt_stub

.align 16
vector_220_handler:
	pushq $0
	pushq $220
	jmp interrupt_stub

.align 16
vector_221_handler:
	pushq $0
	pushq $221
	jmp interrupt_stub

.align 16
vector_222_handler:
	pushq $0
	pushq $222
	jmp interrupt_stub

.align 16
vector_223_handler:
	pushq $0
	pushq $223
	jmp interrupt_stub

.align 16
vector_224_handler:
	pushq $0
	pushq $224
	jmp interrupt_stub

.align 16
vector_225_handler:
	pushq $0
	pushq $225
	jmp interrupt_stub

.align 16
vector_226_handler:
	pushq $0
	pushq $226
	jmp interrupt_stub

.align 16
vector_227_handler:
	pushq $0
	pushq $227
	jmp interrupt_stub

.align 16
vector_228_handler:
	pushq $0
	pushq $228
	jmp interrupt_stub

.align 16
vector_229_handler:
	pushq $0
	pushq $229
	jmp interrupt_stub

.align 16
vector_230_handler:
	pushq $0
	pushq $230
	jmp interrupt_stub

.align 16
vector_231_handler:
	pushq $0
	pushq $231
	jmp interrupt_stub

.align 16
vector_232_handler:
	pushq $0
	pushq $232
	jmp interrupt_stub

.align 16
vector_233_handler:
	pushq $0
	pushq $233
	jmp interrupt_stub

.align 16
vector_234_handler:
	pushq $0
	pushq $234
	jmp interrupt_stub

.align 16
vector_235_handler:
	pushq $0
	pushq $235
	jmp interrupt_stub

.align 16
vector_236_handler:
	pushq $0
	pushq $236
	jmp interrupt_stub

.align 16
vector_237_handler:
	pushq $0
	pushq $237
	jmp interrupt_stub

.align 16
vector_238_handler:
	pushq $0
	pushq $238
	jmp interrupt_stub

.align 16
vector_239_handler:
	pushq $0
	pushq $239
	jmp interrupt_stub

.align 16
vector_240_handler:
	pushq $0
	pushq $240
	jmp interrupt_stub

.align 16
vector_241_handler:
	pushq $0
	pushq $241
	jmp interrupt_stub

.align 16
vector_242_handler:
	pushq $0
	pushq $242
	jmp interrupt_stub

.align 16
vector_243_handler:
	pushq $0
	pushq $243
	jmp interrupt_stub

.align 16
vector_244_handler:
	pushq $0
	pushq $244
	jmp interrupt_stub

.align 16
vector_245_handler:
	pushq $0
	pushq $245
	jmp interrupt_stub

.align 16
vector_246_handler:
	pushq $0
	pushq $246
	jmp interrupt_stub

.align 16
vector_247_handler:
	pushq $0
	pushq $247
	jmp interrupt_stub

.align 16
vector_248_handler:
	pushq $0
	pushq $248
	jmp interrupt_stub

.align 16
vector_249_handler:
	pushq $0
	pushq $249
	jmp interrupt_stub

.align 16
vector_250_handler:
	pushq $0
	pushq $250
	jmp interrupt_stub

.align 16
vector_251_handler:
	pushq $0
	pushq $251
	jmp interrupt_stub

.align 16
vector_252_handler:
	pushq $0
	pushq $252
	jmp interrupt_stub

.align 16
vector_253_handler:
	pushq $0
	pushq $253
	jmp interrupt_stub

.align 16
vector_254_handler:
	pushq $0
	pushq $254
	jmp interrupt_stub

.align 16
vector_255_handler:
	pushq $0
	pushq $255
	jmp interrupt_stub