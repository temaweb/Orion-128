# Intel 8080 (KR580VM80A)

Эмулятор процессора Intel 8080.

* Дата анонса: апрель 1974 года
* Тактовая частота: 2 МГц (позже 2,5 МГц, 3,1 МГц и 4 МГц)
* Разрядность регистров: 8 бит
* Разрядность шины данных: 8 бит
* Разрядность шины адреса: 16 бит
* Объём адресуемой памяти: 64 Кбайт
* Поддерживаемые технологии: 80 инструкций

### 8080 Preliminary tests

    8080 Preliminary tests complete
    
### MICROCOSM ASSOCIATES 8080/8085 CPU DIAGNOSTIC

    MICROCOSM ASSOCIATES 8080/8085 CPU DIAGNOSTIC VERSION 1.0  (C) 1980

    CPU IS OPERATIONAL
    
### DIAGNOSTICS II V1.2 - CPU TEST

    DIAGNOSTICS II V1.2 - CPU TEST
    COPYRIGHT (C) 1981 - SUPERSOFT ASSOCIATES

    ABCDEFGHIJKLMNOPQRSTUVWXYZ
    CPU IS 8080/8085
    BEGIN TIMING TEST
    END TIMING TEST
    CPU TESTS OK
    
### 8080 instruction exerciser by Ian Bartholomew and Frank Cringles

    8080 instruction exerciser

    dad <b,d,h,sp>................  PASS! crc is:14474ba6
    aluop nn......................  PASS! crc is:9e922f9e
    aluop <b,c,d,e,h,l,m,a>.......  PASS! crc is:cf762c86
    <daa,cma,stc,cmc>.............  PASS! crc is:bb3f030c
    <inr,dcr> a...................  PASS! crc is:adb6460e
    <inr,dcr> b...................  PASS! crc is:83ed1345
    <inx,dcx> b...................  PASS! crc is:f79287cd
    <inr,dcr> c...................  PASS! crc is:e5f6721b
    <inr,dcr> d...................  PASS! crc is:15b5579a
    <inx,dcx> d...................  PASS! crc is:7f4e2501
    <inr,dcr> e...................  PASS! crc is:cf2ab396
    <inr,dcr> h...................  PASS! crc is:12b2952c
    <inx,dcx> h...................  PASS! crc is:9f2b23c0
    <inr,dcr> l...................  PASS! crc is:ff57d356
    <inr,dcr> m...................  PASS! crc is:92e963bd
    <inx,dcx> sp..................  PASS! crc is:d5702fab
    lhld nnnn.....................  PASS! crc is:a9c3d5cb
    shld nnnn.....................  PASS! crc is:e8864f26
    lxi <b,d,h,sp>,nnnn...........  PASS! crc is:fcf46e12
    ldax <b,d>....................  PASS! crc is:2b821d5f
    mvi <b,c,d,e,h,l,m,a>,nn......  PASS! crc is:eaa72044
    mov <bcdehla>,<bcdehla>.......  PASS! crc is:10b58cee
    sta nnnn / lda nnnn...........  PASS! crc is:ed57af72
    <rlc,rrc,ral,rar>.............  PASS! crc is:e0d89235
    stax <b,d>....................  PASS! crc is:2b0471e9

    Tests complete
