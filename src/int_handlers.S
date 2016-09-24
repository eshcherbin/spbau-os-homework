.text
.code64

// in simple handlers there are fake error codes
#define HANDLER(n) \
handler##n: \
    pushq $0; \
    pushq $##n; \
    jmp common_prehandler; \


#define HANDLER_EXC(n) \
handler##n: \
    pushq $##n; \
    jmp common_prehandler; \


HANDLER(0)
HANDLER(1)
HANDLER(2)
HANDLER(3)
HANDLER(4)
HANDLER(5)
HANDLER(6)
HANDLER(7)
HANDLER_EXC(8)
HANDLER(9)
HANDLER_EXC(10)
HANDLER_EXC(11)
HANDLER_EXC(12)
HANDLER_EXC(13)
HANDLER_EXC(14)
HANDLER(15)
HANDLER(16)
HANDLER_EXC(17)
HANDLER(18)
HANDLER(19)
HANDLER(20)
HANDLER(21)
HANDLER(22)
HANDLER(23)
HANDLER(24)
HANDLER(25)
HANDLER(26)
HANDLER(27)
HANDLER(28)
HANDLER(29)
HANDLER(30)
HANDLER(31)
HANDLER(32)
HANDLER(33)
HANDLER(34)
HANDLER(35)
HANDLER(36)
HANDLER(37)
HANDLER(38)
HANDLER(39)
HANDLER(40)
HANDLER(41)
HANDLER(42)
HANDLER(43)
HANDLER(44)
HANDLER(45)
HANDLER(46)
HANDLER(47)
HANDLER(48)
HANDLER(49)
HANDLER(50)
HANDLER(51)
HANDLER(52)
HANDLER(53)
HANDLER(54)
HANDLER(55)
HANDLER(56)
HANDLER(57)
HANDLER(58)
HANDLER(59)
HANDLER(60)
HANDLER(61)
HANDLER(62)
HANDLER(63)
HANDLER(64)
HANDLER(65)
HANDLER(66)
HANDLER(67)
HANDLER(68)
HANDLER(69)
HANDLER(70)
HANDLER(71)
HANDLER(72)
HANDLER(73)
HANDLER(74)
HANDLER(75)
HANDLER(76)
HANDLER(77)
HANDLER(78)
HANDLER(79)
HANDLER(80)
HANDLER(81)
HANDLER(82)
HANDLER(83)
HANDLER(84)
HANDLER(85)
HANDLER(86)
HANDLER(87)
HANDLER(88)
HANDLER(89)
HANDLER(90)
HANDLER(91)
HANDLER(92)
HANDLER(93)
HANDLER(94)
HANDLER(95)
HANDLER(96)
HANDLER(97)
HANDLER(98)
HANDLER(99)
HANDLER(100)
HANDLER(101)
HANDLER(102)
HANDLER(103)
HANDLER(104)
HANDLER(105)
HANDLER(106)
HANDLER(107)
HANDLER(108)
HANDLER(109)
HANDLER(110)
HANDLER(111)
HANDLER(112)
HANDLER(113)
HANDLER(114)
HANDLER(115)
HANDLER(116)
HANDLER(117)
HANDLER(118)
HANDLER(119)
HANDLER(120)
HANDLER(121)
HANDLER(122)
HANDLER(123)
HANDLER(124)
HANDLER(125)
HANDLER(126)
HANDLER(127)
HANDLER(128)
HANDLER(129)
HANDLER(130)
HANDLER(131)
HANDLER(132)
HANDLER(133)
HANDLER(134)
HANDLER(135)
HANDLER(136)
HANDLER(137)
HANDLER(138)
HANDLER(139)
HANDLER(140)
HANDLER(141)
HANDLER(142)
HANDLER(143)
HANDLER(144)
HANDLER(145)
HANDLER(146)
HANDLER(147)
HANDLER(148)
HANDLER(149)
HANDLER(150)
HANDLER(151)
HANDLER(152)
HANDLER(153)
HANDLER(154)
HANDLER(155)
HANDLER(156)
HANDLER(157)
HANDLER(158)
HANDLER(159)
HANDLER(160)
HANDLER(161)
HANDLER(162)
HANDLER(163)
HANDLER(164)
HANDLER(165)
HANDLER(166)
HANDLER(167)
HANDLER(168)
HANDLER(169)
HANDLER(170)
HANDLER(171)
HANDLER(172)
HANDLER(173)
HANDLER(174)
HANDLER(175)
HANDLER(176)
HANDLER(177)
HANDLER(178)
HANDLER(179)
HANDLER(180)
HANDLER(181)
HANDLER(182)
HANDLER(183)
HANDLER(184)
HANDLER(185)
HANDLER(186)
HANDLER(187)
HANDLER(188)
HANDLER(189)
HANDLER(190)
HANDLER(191)
HANDLER(192)
HANDLER(193)
HANDLER(194)
HANDLER(195)
HANDLER(196)
HANDLER(197)
HANDLER(198)
HANDLER(199)
HANDLER(200)
HANDLER(201)
HANDLER(202)
HANDLER(203)
HANDLER(204)
HANDLER(205)
HANDLER(206)
HANDLER(207)
HANDLER(208)
HANDLER(209)
HANDLER(210)
HANDLER(211)
HANDLER(212)
HANDLER(213)
HANDLER(214)
HANDLER(215)
HANDLER(216)
HANDLER(217)
HANDLER(218)
HANDLER(219)
HANDLER(220)
HANDLER(221)
HANDLER(222)
HANDLER(223)
HANDLER(224)
HANDLER(225)
HANDLER(226)
HANDLER(227)
HANDLER(228)
HANDLER(229)
HANDLER(230)
HANDLER(231)
HANDLER(232)
HANDLER(233)
HANDLER(234)
HANDLER(235)
HANDLER(236)
HANDLER(237)
HANDLER(238)
HANDLER(239)
HANDLER(240)
HANDLER(241)
HANDLER(242)
HANDLER(243)
HANDLER(244)
HANDLER(245)
HANDLER(246)
HANDLER(247)
HANDLER(248)
HANDLER(249)
HANDLER(250)
HANDLER(251)
HANDLER(252)
HANDLER(253)
HANDLER(254)
HANDLER(255)

.global interrupt_handlers
interrupt_handlers:
    .quad handler0
    .quad handler1
    .quad handler2
    .quad handler3
    .quad handler4
    .quad handler5
    .quad handler6
    .quad handler7
    .quad handler8
    .quad handler9
    .quad handler10
    .quad handler11
    .quad handler12
    .quad handler13
    .quad handler14
    .quad handler15
    .quad handler16
    .quad handler17
    .quad handler18
    .quad handler19
    .quad handler20
    .quad handler21
    .quad handler22
    .quad handler23
    .quad handler24
    .quad handler25
    .quad handler26
    .quad handler27
    .quad handler28
    .quad handler29
    .quad handler30
    .quad handler31
    .quad handler32
    .quad handler33
    .quad handler34
    .quad handler35
    .quad handler36
    .quad handler37
    .quad handler38
    .quad handler39
    .quad handler40
    .quad handler41
    .quad handler42
    .quad handler43
    .quad handler44
    .quad handler45
    .quad handler46
    .quad handler47
    .quad handler48
    .quad handler49
    .quad handler50
    .quad handler51
    .quad handler52
    .quad handler53
    .quad handler54
    .quad handler55
    .quad handler56
    .quad handler57
    .quad handler58
    .quad handler59
    .quad handler60
    .quad handler61
    .quad handler62
    .quad handler63
    .quad handler64
    .quad handler65
    .quad handler66
    .quad handler67
    .quad handler68
    .quad handler69
    .quad handler70
    .quad handler71
    .quad handler72
    .quad handler73
    .quad handler74
    .quad handler75
    .quad handler76
    .quad handler77
    .quad handler78
    .quad handler79
    .quad handler80
    .quad handler81
    .quad handler82
    .quad handler83
    .quad handler84
    .quad handler85
    .quad handler86
    .quad handler87
    .quad handler88
    .quad handler89
    .quad handler90
    .quad handler91
    .quad handler92
    .quad handler93
    .quad handler94
    .quad handler95
    .quad handler96
    .quad handler97
    .quad handler98
    .quad handler99
    .quad handler100
    .quad handler101
    .quad handler102
    .quad handler103
    .quad handler104
    .quad handler105
    .quad handler106
    .quad handler107
    .quad handler108
    .quad handler109
    .quad handler110
    .quad handler111
    .quad handler112
    .quad handler113
    .quad handler114
    .quad handler115
    .quad handler116
    .quad handler117
    .quad handler118
    .quad handler119
    .quad handler120
    .quad handler121
    .quad handler122
    .quad handler123
    .quad handler124
    .quad handler125
    .quad handler126
    .quad handler127
    .quad handler128
    .quad handler129
    .quad handler130
    .quad handler131
    .quad handler132
    .quad handler133
    .quad handler134
    .quad handler135
    .quad handler136
    .quad handler137
    .quad handler138
    .quad handler139
    .quad handler140
    .quad handler141
    .quad handler142
    .quad handler143
    .quad handler144
    .quad handler145
    .quad handler146
    .quad handler147
    .quad handler148
    .quad handler149
    .quad handler150
    .quad handler151
    .quad handler152
    .quad handler153
    .quad handler154
    .quad handler155
    .quad handler156
    .quad handler157
    .quad handler158
    .quad handler159
    .quad handler160
    .quad handler161
    .quad handler162
    .quad handler163
    .quad handler164
    .quad handler165
    .quad handler166
    .quad handler167
    .quad handler168
    .quad handler169
    .quad handler170
    .quad handler171
    .quad handler172
    .quad handler173
    .quad handler174
    .quad handler175
    .quad handler176
    .quad handler177
    .quad handler178
    .quad handler179
    .quad handler180
    .quad handler181
    .quad handler182
    .quad handler183
    .quad handler184
    .quad handler185
    .quad handler186
    .quad handler187
    .quad handler188
    .quad handler189
    .quad handler190
    .quad handler191
    .quad handler192
    .quad handler193
    .quad handler194
    .quad handler195
    .quad handler196
    .quad handler197
    .quad handler198
    .quad handler199
    .quad handler200
    .quad handler201
    .quad handler202
    .quad handler203
    .quad handler204
    .quad handler205
    .quad handler206
    .quad handler207
    .quad handler208
    .quad handler209
    .quad handler210
    .quad handler211
    .quad handler212
    .quad handler213
    .quad handler214
    .quad handler215
    .quad handler216
    .quad handler217
    .quad handler218
    .quad handler219
    .quad handler220
    .quad handler221
    .quad handler222
    .quad handler223
    .quad handler224
    .quad handler225
    .quad handler226
    .quad handler227
    .quad handler228
    .quad handler229
    .quad handler230
    .quad handler231
    .quad handler232
    .quad handler233
    .quad handler234
    .quad handler235
    .quad handler236
    .quad handler237
    .quad handler238
    .quad handler239
    .quad handler240
    .quad handler241
    .quad handler242
    .quad handler243
    .quad handler244
    .quad handler245
    .quad handler246
    .quad handler247
    .quad handler248
    .quad handler249
    .quad handler250
    .quad handler251
    .quad handler252
    .quad handler253
    .quad handler254
    .quad handler255

common_prehandler:
    
    pushq %rdi

    // pass one uint64_t (interrupt_id) as a parameter
    movq 8(%rsp), %rdi 

    pushq %rax
    pushq %rbx
    pushq %rcx
    pushq %rdx
    pushq %rbp
    pushq %rdi
    pushq %rsi
    pushq %r9
    pushq %r10
    pushq %r11
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15

    call common_handler

    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %r11
    popq %r10
    popq %r9
    popq %rsi
    popq %rdi
    popq %rbp
    popq %rdx
    popq %rcx
    popq %rbx
    popq %rax

    popq %rdi

    addq $16, %rsp // pop error code and interrupt id

    iretq
