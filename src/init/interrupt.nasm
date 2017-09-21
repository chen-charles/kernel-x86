%include    "/../asm.inc"

global int_handler_0
global int_handler_1
global int_handler_2
global int_handler_3
global int_handler_4
global int_handler_5
global int_handler_6
global int_handler_7
global int_handler_8
global int_handler_9
global int_handler_10
global int_handler_11
global int_handler_12
global int_handler_13
global int_handler_14
global int_handler_15
global int_handler_16
global int_handler_17
global int_handler_18
global int_handler_19
global int_handler_20
global int_handler_21
global int_handler_22
global int_handler_23
global int_handler_24
global int_handler_25
global int_handler_26
global int_handler_27
global int_handler_28
global int_handler_29
global int_handler_30
global int_handler_31
global int_handler_32
global int_handler_33
global int_handler_34
global int_handler_35
global int_handler_36
global int_handler_37
global int_handler_38
global int_handler_39
global int_handler_40
global int_handler_41
global int_handler_42
global int_handler_43
global int_handler_44
global int_handler_45
global int_handler_46
global int_handler_47
global int_handler_48
global int_handler_49
global int_handler_50
global int_handler_51
global int_handler_52
global int_handler_53
global int_handler_54
global int_handler_55
global int_handler_56
global int_handler_57
global int_handler_58
global int_handler_59
global int_handler_60
global int_handler_61
global int_handler_62
global int_handler_63
global int_handler_64
global int_handler_65
global int_handler_66
global int_handler_67
global int_handler_68
global int_handler_69
global int_handler_70
global int_handler_71
global int_handler_72
global int_handler_73
global int_handler_74
global int_handler_75
global int_handler_76
global int_handler_77
global int_handler_78
global int_handler_79
global int_handler_80
global int_handler_81
global int_handler_82
global int_handler_83
global int_handler_84
global int_handler_85
global int_handler_86
global int_handler_87
global int_handler_88
global int_handler_89
global int_handler_90
global int_handler_91
global int_handler_92
global int_handler_93
global int_handler_94
global int_handler_95
global int_handler_96
global int_handler_97
global int_handler_98
global int_handler_99
global int_handler_100
global int_handler_101
global int_handler_102
global int_handler_103
global int_handler_104
global int_handler_105
global int_handler_106
global int_handler_107
global int_handler_108
global int_handler_109
global int_handler_110
global int_handler_111
global int_handler_112
global int_handler_113
global int_handler_114
global int_handler_115
global int_handler_116
global int_handler_117
global int_handler_118
global int_handler_119
global int_handler_120
global int_handler_121
global int_handler_122
global int_handler_123
global int_handler_124
global int_handler_125
global int_handler_126
global int_handler_127
global int_handler_128
global int_handler_129
global int_handler_130
global int_handler_131
global int_handler_132
global int_handler_133
global int_handler_134
global int_handler_135
global int_handler_136
global int_handler_137
global int_handler_138
global int_handler_139
global int_handler_140
global int_handler_141
global int_handler_142
global int_handler_143
global int_handler_144
global int_handler_145
global int_handler_146
global int_handler_147
global int_handler_148
global int_handler_149
global int_handler_150
global int_handler_151
global int_handler_152
global int_handler_153
global int_handler_154
global int_handler_155
global int_handler_156
global int_handler_157
global int_handler_158
global int_handler_159
global int_handler_160
global int_handler_161
global int_handler_162
global int_handler_163
global int_handler_164
global int_handler_165
global int_handler_166
global int_handler_167
global int_handler_168
global int_handler_169
global int_handler_170
global int_handler_171
global int_handler_172
global int_handler_173
global int_handler_174
global int_handler_175
global int_handler_176
global int_handler_177
global int_handler_178
global int_handler_179
global int_handler_180
global int_handler_181
global int_handler_182
global int_handler_183
global int_handler_184
global int_handler_185
global int_handler_186
global int_handler_187
global int_handler_188
global int_handler_189
global int_handler_190
global int_handler_191
global int_handler_192
global int_handler_193
global int_handler_194
global int_handler_195
global int_handler_196
global int_handler_197
global int_handler_198
global int_handler_199
global int_handler_200
global int_handler_201
global int_handler_202
global int_handler_203
global int_handler_204
global int_handler_205
global int_handler_206
global int_handler_207
global int_handler_208
global int_handler_209
global int_handler_210
global int_handler_211
global int_handler_212
global int_handler_213
global int_handler_214
global int_handler_215
global int_handler_216
global int_handler_217
global int_handler_218
global int_handler_219
global int_handler_220
global int_handler_221
global int_handler_222
global int_handler_223
global int_handler_224
global int_handler_225
global int_handler_226
global int_handler_227
global int_handler_228
global int_handler_229
global int_handler_230
global int_handler_231
global int_handler_232
global int_handler_233
global int_handler_234
global int_handler_235
global int_handler_236
global int_handler_237
global int_handler_238
global int_handler_239
global int_handler_240
global int_handler_241
global int_handler_242
global int_handler_243
global int_handler_244
global int_handler_245
global int_handler_246
global int_handler_247
global int_handler_248
global int_handler_249
global int_handler_250
global int_handler_251
global int_handler_252
global int_handler_253
global int_handler_254
global int_handler_255

extern interrupt

bits 32
align 4

int_handler_0:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	0
	jmp	interrupt_ret


int_handler_1:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	1
	jmp	interrupt_ret


int_handler_2:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	2
	jmp	interrupt_ret


int_handler_3:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	3
	jmp	interrupt_ret


int_handler_4:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	4
	jmp	interrupt_ret


int_handler_5:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	5
	jmp	interrupt_ret


int_handler_6:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	6
	jmp	interrupt_ret


int_handler_7:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	7
	jmp	interrupt_ret


int_handler_8:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	8
	jmp	interrupt_ret


int_handler_9:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	9
	jmp	interrupt_ret


int_handler_10:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	10
	jmp	interrupt_ret


int_handler_11:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	11
	jmp	interrupt_ret


int_handler_12:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	12
	jmp	interrupt_ret


int_handler_13:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	13
	jmp	interrupt_ret


int_handler_14:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	14
	jmp	interrupt_ret


int_handler_15:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	15
	jmp	interrupt_ret


int_handler_16:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	16
	jmp	interrupt_ret


int_handler_17:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	17
	jmp	interrupt_ret


int_handler_18:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	18
	jmp	interrupt_ret


int_handler_19:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	19
	jmp	interrupt_ret


int_handler_20:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	20
	jmp	interrupt_ret


int_handler_21:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	21
	jmp	interrupt_ret


int_handler_22:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	22
	jmp	interrupt_ret


int_handler_23:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	23
	jmp	interrupt_ret


int_handler_24:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	24
	jmp	interrupt_ret


int_handler_25:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	25
	jmp	interrupt_ret


int_handler_26:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	26
	jmp	interrupt_ret


int_handler_27:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	27
	jmp	interrupt_ret


int_handler_28:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	28
	jmp	interrupt_ret


int_handler_29:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	29
	jmp	interrupt_ret


int_handler_30:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	30
	jmp	interrupt_ret


int_handler_31:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	31
	jmp	interrupt_ret


int_handler_32:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	32
	jmp	interrupt_ret


int_handler_33:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	33
	jmp	interrupt_ret


int_handler_34:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	34
	jmp	interrupt_ret


int_handler_35:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	35
	jmp	interrupt_ret


int_handler_36:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	36
	jmp	interrupt_ret


int_handler_37:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	37
	jmp	interrupt_ret


int_handler_38:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	38
	jmp	interrupt_ret


int_handler_39:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	39
	jmp	interrupt_ret


int_handler_40:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	40
	jmp	interrupt_ret


int_handler_41:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	41
	jmp	interrupt_ret


int_handler_42:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	42
	jmp	interrupt_ret


int_handler_43:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	43
	jmp	interrupt_ret


int_handler_44:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	44
	jmp	interrupt_ret


int_handler_45:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	45
	jmp	interrupt_ret


int_handler_46:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	46
	jmp	interrupt_ret


int_handler_47:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	47
	jmp	interrupt_ret


int_handler_48:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	48
	jmp	interrupt_ret


int_handler_49:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	49
	jmp	interrupt_ret


int_handler_50:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	50
	jmp	interrupt_ret


int_handler_51:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	51
	jmp	interrupt_ret


int_handler_52:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	52
	jmp	interrupt_ret


int_handler_53:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	53
	jmp	interrupt_ret


int_handler_54:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	54
	jmp	interrupt_ret


int_handler_55:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	55
	jmp	interrupt_ret


int_handler_56:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	56
	jmp	interrupt_ret


int_handler_57:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	57
	jmp	interrupt_ret


int_handler_58:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	58
	jmp	interrupt_ret


int_handler_59:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	59
	jmp	interrupt_ret


int_handler_60:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	60
	jmp	interrupt_ret


int_handler_61:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	61
	jmp	interrupt_ret


int_handler_62:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	62
	jmp	interrupt_ret


int_handler_63:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	63
	jmp	interrupt_ret


int_handler_64:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	64
	jmp	interrupt_ret


int_handler_65:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	65
	jmp	interrupt_ret


int_handler_66:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	66
	jmp	interrupt_ret


int_handler_67:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	67
	jmp	interrupt_ret


int_handler_68:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	68
	jmp	interrupt_ret


int_handler_69:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	69
	jmp	interrupt_ret


int_handler_70:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	70
	jmp	interrupt_ret


int_handler_71:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	71
	jmp	interrupt_ret


int_handler_72:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	72
	jmp	interrupt_ret


int_handler_73:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	73
	jmp	interrupt_ret


int_handler_74:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	74
	jmp	interrupt_ret


int_handler_75:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	75
	jmp	interrupt_ret


int_handler_76:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	76
	jmp	interrupt_ret


int_handler_77:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	77
	jmp	interrupt_ret


int_handler_78:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	78
	jmp	interrupt_ret


int_handler_79:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	79
	jmp	interrupt_ret


int_handler_80:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	80
	jmp	interrupt_ret


int_handler_81:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	81
	jmp	interrupt_ret


int_handler_82:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	82
	jmp	interrupt_ret


int_handler_83:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	83
	jmp	interrupt_ret


int_handler_84:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	84
	jmp	interrupt_ret


int_handler_85:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	85
	jmp	interrupt_ret


int_handler_86:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	86
	jmp	interrupt_ret


int_handler_87:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	87
	jmp	interrupt_ret


int_handler_88:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	88
	jmp	interrupt_ret


int_handler_89:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	89
	jmp	interrupt_ret


int_handler_90:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	90
	jmp	interrupt_ret


int_handler_91:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	91
	jmp	interrupt_ret


int_handler_92:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	92
	jmp	interrupt_ret


int_handler_93:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	93
	jmp	interrupt_ret


int_handler_94:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	94
	jmp	interrupt_ret


int_handler_95:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	95
	jmp	interrupt_ret


int_handler_96:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	96
	jmp	interrupt_ret


int_handler_97:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	97
	jmp	interrupt_ret


int_handler_98:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	98
	jmp	interrupt_ret


int_handler_99:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	99
	jmp	interrupt_ret


int_handler_100:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	100
	jmp	interrupt_ret


int_handler_101:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	101
	jmp	interrupt_ret


int_handler_102:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	102
	jmp	interrupt_ret


int_handler_103:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	103
	jmp	interrupt_ret


int_handler_104:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	104
	jmp	interrupt_ret


int_handler_105:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	105
	jmp	interrupt_ret


int_handler_106:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	106
	jmp	interrupt_ret


int_handler_107:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	107
	jmp	interrupt_ret


int_handler_108:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	108
	jmp	interrupt_ret


int_handler_109:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	109
	jmp	interrupt_ret


int_handler_110:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	110
	jmp	interrupt_ret


int_handler_111:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	111
	jmp	interrupt_ret


int_handler_112:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	112
	jmp	interrupt_ret


int_handler_113:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	113
	jmp	interrupt_ret


int_handler_114:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	114
	jmp	interrupt_ret


int_handler_115:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	115
	jmp	interrupt_ret


int_handler_116:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	116
	jmp	interrupt_ret


int_handler_117:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	117
	jmp	interrupt_ret


int_handler_118:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	118
	jmp	interrupt_ret


int_handler_119:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	119
	jmp	interrupt_ret


int_handler_120:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	120
	jmp	interrupt_ret


int_handler_121:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	121
	jmp	interrupt_ret


int_handler_122:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	122
	jmp	interrupt_ret


int_handler_123:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	123
	jmp	interrupt_ret


int_handler_124:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	124
	jmp	interrupt_ret


int_handler_125:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	125
	jmp	interrupt_ret


int_handler_126:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	126
	jmp	interrupt_ret


int_handler_127:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	127
	jmp	interrupt_ret


int_handler_128:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	128
	jmp	interrupt_ret


int_handler_129:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	129
	jmp	interrupt_ret


int_handler_130:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	130
	jmp	interrupt_ret


int_handler_131:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	131
	jmp	interrupt_ret


int_handler_132:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	132
	jmp	interrupt_ret


int_handler_133:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	133
	jmp	interrupt_ret


int_handler_134:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	134
	jmp	interrupt_ret


int_handler_135:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	135
	jmp	interrupt_ret


int_handler_136:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	136
	jmp	interrupt_ret


int_handler_137:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	137
	jmp	interrupt_ret


int_handler_138:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	138
	jmp	interrupt_ret


int_handler_139:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	139
	jmp	interrupt_ret


int_handler_140:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	140
	jmp	interrupt_ret


int_handler_141:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	141
	jmp	interrupt_ret


int_handler_142:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	142
	jmp	interrupt_ret


int_handler_143:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	143
	jmp	interrupt_ret


int_handler_144:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	144
	jmp	interrupt_ret


int_handler_145:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	145
	jmp	interrupt_ret


int_handler_146:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	146
	jmp	interrupt_ret


int_handler_147:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	147
	jmp	interrupt_ret


int_handler_148:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	148
	jmp	interrupt_ret


int_handler_149:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	149
	jmp	interrupt_ret


int_handler_150:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	150
	jmp	interrupt_ret


int_handler_151:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	151
	jmp	interrupt_ret


int_handler_152:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	152
	jmp	interrupt_ret


int_handler_153:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	153
	jmp	interrupt_ret


int_handler_154:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	154
	jmp	interrupt_ret


int_handler_155:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	155
	jmp	interrupt_ret


int_handler_156:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	156
	jmp	interrupt_ret


int_handler_157:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	157
	jmp	interrupt_ret


int_handler_158:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	158
	jmp	interrupt_ret


int_handler_159:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	159
	jmp	interrupt_ret


int_handler_160:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	160
	jmp	interrupt_ret


int_handler_161:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	161
	jmp	interrupt_ret


int_handler_162:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	162
	jmp	interrupt_ret


int_handler_163:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	163
	jmp	interrupt_ret


int_handler_164:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	164
	jmp	interrupt_ret


int_handler_165:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	165
	jmp	interrupt_ret


int_handler_166:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	166
	jmp	interrupt_ret


int_handler_167:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	167
	jmp	interrupt_ret


int_handler_168:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	168
	jmp	interrupt_ret


int_handler_169:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	169
	jmp	interrupt_ret


int_handler_170:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	170
	jmp	interrupt_ret


int_handler_171:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	171
	jmp	interrupt_ret


int_handler_172:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	172
	jmp	interrupt_ret


int_handler_173:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	173
	jmp	interrupt_ret


int_handler_174:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	174
	jmp	interrupt_ret


int_handler_175:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	175
	jmp	interrupt_ret


int_handler_176:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	176
	jmp	interrupt_ret


int_handler_177:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	177
	jmp	interrupt_ret


int_handler_178:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	178
	jmp	interrupt_ret


int_handler_179:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	179
	jmp	interrupt_ret


int_handler_180:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	180
	jmp	interrupt_ret


int_handler_181:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	181
	jmp	interrupt_ret


int_handler_182:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	182
	jmp	interrupt_ret


int_handler_183:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	183
	jmp	interrupt_ret


int_handler_184:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	184
	jmp	interrupt_ret


int_handler_185:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	185
	jmp	interrupt_ret


int_handler_186:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	186
	jmp	interrupt_ret


int_handler_187:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	187
	jmp	interrupt_ret


int_handler_188:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	188
	jmp	interrupt_ret


int_handler_189:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	189
	jmp	interrupt_ret


int_handler_190:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	190
	jmp	interrupt_ret


int_handler_191:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	191
	jmp	interrupt_ret


int_handler_192:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	192
	jmp	interrupt_ret


int_handler_193:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	193
	jmp	interrupt_ret


int_handler_194:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	194
	jmp	interrupt_ret


int_handler_195:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	195
	jmp	interrupt_ret


int_handler_196:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	196
	jmp	interrupt_ret


int_handler_197:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	197
	jmp	interrupt_ret


int_handler_198:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	198
	jmp	interrupt_ret


int_handler_199:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	199
	jmp	interrupt_ret


int_handler_200:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	200
	jmp	interrupt_ret


int_handler_201:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	201
	jmp	interrupt_ret


int_handler_202:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	202
	jmp	interrupt_ret


int_handler_203:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	203
	jmp	interrupt_ret


int_handler_204:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	204
	jmp	interrupt_ret


int_handler_205:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	205
	jmp	interrupt_ret


int_handler_206:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	206
	jmp	interrupt_ret


int_handler_207:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	207
	jmp	interrupt_ret


int_handler_208:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	208
	jmp	interrupt_ret


int_handler_209:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	209
	jmp	interrupt_ret


int_handler_210:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	210
	jmp	interrupt_ret


int_handler_211:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	211
	jmp	interrupt_ret


int_handler_212:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	212
	jmp	interrupt_ret


int_handler_213:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	213
	jmp	interrupt_ret


int_handler_214:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	214
	jmp	interrupt_ret


int_handler_215:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	215
	jmp	interrupt_ret


int_handler_216:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	216
	jmp	interrupt_ret


int_handler_217:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	217
	jmp	interrupt_ret


int_handler_218:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	218
	jmp	interrupt_ret


int_handler_219:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	219
	jmp	interrupt_ret


int_handler_220:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	220
	jmp	interrupt_ret


int_handler_221:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	221
	jmp	interrupt_ret


int_handler_222:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	222
	jmp	interrupt_ret


int_handler_223:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	223
	jmp	interrupt_ret


int_handler_224:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	224
	jmp	interrupt_ret


int_handler_225:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	225
	jmp	interrupt_ret


int_handler_226:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	226
	jmp	interrupt_ret


int_handler_227:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	227
	jmp	interrupt_ret


int_handler_228:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	228
	jmp	interrupt_ret


int_handler_229:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	229
	jmp	interrupt_ret


int_handler_230:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	230
	jmp	interrupt_ret


int_handler_231:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	231
	jmp	interrupt_ret


int_handler_232:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	232
	jmp	interrupt_ret


int_handler_233:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	233
	jmp	interrupt_ret


int_handler_234:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	234
	jmp	interrupt_ret


int_handler_235:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	235
	jmp	interrupt_ret


int_handler_236:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	236
	jmp	interrupt_ret


int_handler_237:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	237
	jmp	interrupt_ret


int_handler_238:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	238
	jmp	interrupt_ret


int_handler_239:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	239
	jmp	interrupt_ret


int_handler_240:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	240
	jmp	interrupt_ret


int_handler_241:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	241
	jmp	interrupt_ret


int_handler_242:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	242
	jmp	interrupt_ret


int_handler_243:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	243
	jmp	interrupt_ret


int_handler_244:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	244
	jmp	interrupt_ret


int_handler_245:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	245
	jmp	interrupt_ret


int_handler_246:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	246
	jmp	interrupt_ret


int_handler_247:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	247
	jmp	interrupt_ret


int_handler_248:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	248
	jmp	interrupt_ret


int_handler_249:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	249
	jmp	interrupt_ret


int_handler_250:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	250
	jmp	interrupt_ret


int_handler_251:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	251
	jmp	interrupt_ret


int_handler_252:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	252
	jmp	interrupt_ret


int_handler_253:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	253
	jmp	interrupt_ret


int_handler_254:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	254
	jmp	interrupt_ret


int_handler_255:
	push	eax
	xor	eax, eax
	mov	ax, ds
	push	eax
	mov	ax, es
	push	eax
	mov	ax, fs
	push	eax
	mov	ax, gs
	push	eax
	pushad
	push	255
	jmp	interrupt_ret


last_int:
    db  0

interrupt_ret:
    cld

    mov eax, esp
    add eax, 4  ;intr. number
    add eax, 32 ;pushad 32 bytes
    add eax, 20  ;segment
    push eax	;pass original stack pointer

    mov ax, ss  ;kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov eax, dword [esp+4]
    mov [last_int], al

    ;change iopl to 0 so that the IF(interrupt flag) will be restored after handling an interrupt from outer rings
    ;pushf
    ;pop	eax
    ;and	eax, 0b1100111111111111
    ;push	eax
    ;popf

    call interrupt
    add esp, 8  ;only pushad is left in stack

    cmp eax, 0x45525243 ; E R R C (error code needs to get poped)
    je .pop_errcode

    test eax, eax
    jz .cont

    cmp eax, 1
    je .die

    sub esp, 8
    call eax
    add esp, 8

.cont:

    ;jmp .3

    ;APIC EOI Register, write 0 to signal
    ;handled in syscall, avoiding paging access-r error #PG
    ;mov al, [SYS_FSC_ENABLED_ADDR]  ;test if fsc is ready
    ;test al, al

    ;fsc not yet, still in ring0, OK access phy mem addr
    mov	ebx, 0xfee00000 ;lapic eoi
    mov	dword [ebx+0xb0], 0
    jmp .3

;uncomment after fsc and ioapic
.scinfo:    
    db  0
    dd  0, 0, 0
.1:
;    pushad
;    mov ecx, esp
;    lea edx, [.2]
;    lea eax, [.scinfo]
;    sysenter
.2:
;    popad

.3:
    add esp, 32 ;fake popad here
    add esp, 20 ;fake pop segreg

    pop	eax
    pop	ebx
    pop	ecx
    or	ecx, 0x200	;enable interrupts after iretd
    push 	ecx
    push	ebx
    push	eax

    sub esp, 20
    sub esp, 32 ;sub esp back to the copy of registers
    popad   ;restore machine state before interrupt

    pop eax
    mov gs, ax
    pop eax
    mov fs, ax
    pop eax
    mov es, ax
    pop eax
    mov ds, ax
    pop eax

    iretd
    nop

.die:
    cli
    mov ebx, eax
    mov al, [last_int]
    mov ecx, 0xffffffff
    mov edx, 0xffffffff
    xchg bx, bx
    popad
    jmp $
    
.pop_errcode:
    add esp, 32
    add esp, 12

    add esp, 2  ; pop errorcode (2 bytes)
    
    sub esp, 12
    sub esp, 32

    xor eax, eax
    jmp .cont
    