; support.inc
; Copyright (c) 2009-2012 mik 
; All rights reserved.


;*
;* ��������ʵ������֧��ͷ�ļ�
;*

%ifndef SUPPORT_INC
%define SUPPORT_INC


%include "cpu.inc"
%include "lib.inc"
%include "clib.inc"
%include "ports.inc"
%include "pci.inc"
%include "debug.inc"
%include "apic.inc"
%include "float.inc"        
%include "task.inc"
%include "sse.inc"
%include "perfmon.inc"
%include "page.inc"
%include "ioapic.inc"
%include "keycode.inc"
%include "hpet.inc"
        
;*
;* ����������� segment
;*

; # BOOT_SEG Ϊ MBR ������
; # SETUP_SEG Ϊ���غ�ı���ģʽ��ʼ���öΣ�sector 0 ������������ص��˴�
; # LIB16_SEG ��ʵģʽ�µĿ⣬�����ص� 8C00h �ڴ洦
; # LIB32_SEG �Ǳ���ģʽ�µĿ⣬�����ص� 0F000h �ڴ洦
; # PROTECTED_SEG �Ǳ���ģʽ�µ����д��룬�����ص� 9000h �ڴ洦
; # LONG_SEG �� long mode ���еĴ��룬�����ص� 10000h �ڴ洦

BOOT_SEG                equ     7c00h
SETUP_SEG               equ     8000h
LIB16_SEG               equ     8A00h
PROTECTED_SEG           equ     9000h
LIB32_SEG               equ     0F000h
LONG_SEG                equ     10000h

;* 
;* change log: LIB32_SEG ���޸ĵ� 0E000h �ڴ洦!
;*
;* change log: LIB32_SEG ���޸ĵ� 0F000h �ڴ洦!
;*


;*
;* �������ӳ������
;*

; # BOOT_SECTOR Ϊ���̵� sector 0
; # SETUP_SECTOR Ϊ���̵� sector 1
; # LIB16_SECTOR Ϊ���̵� sector 20
; # LONG_SECTOR �ڴ��̵� sector 40
; # PROTECTED ģ���޸ĵ��� 64 ����
; # LONG ģ���޸ĵ� 128 ����
; # LIB32 ģ���޸ĵ� 192 ����

BOOT_SECTOR             equ     0
SETUP_SECTOR            equ     1
LIB16_SECTOR            equ     20
LIB32_SECTOR            equ     192
PROTECTED_SECTOR        equ     64
LONG_SECTOR             equ     128

;*
;* change log: �޸��� PROTECTED_SECTOR, LIB32_SECTOR, LONG_SECTOR ������λ��
;*

;* 
;* ������ merge �ϲ����ߵ�����ʵ��
;* ��������Ĵ��������ṹд��ӳ���ļ�
;* 
; # ..\..\common\uboot,0,c.img,63,1     # uboot д�� c.img 63 ������
; # ..\..\common\setup,0,c.img,1,4      # setup д�� c.img 1 ������
; # ..\..\lib\lib16,0,c.img,20,2        # lib16 д�� c.img 20 ������
; # ..\..\lib\lib32,0,c.img,192,10      # 1ib32 д�� c.img 192 ������
; # protected,0,c.img,64,30             # protected д�� c.img 64 ������
; # long,0,c.img,128,20                 # long д�� c.img 128 ������






;*
;* floppy ����
;*

; # SPT(sector per track): ÿ�ŵ��ϵ� sector ��
; # HPC(head per cylinder): ÿ�� cylinder �� head ��

%define SPT             18
%define HPC             2



;*
;* ����Ϊ����
;*


;------------------------------------------------
; ��: LBA_TO_CHS
; ����:
;       ���� 1: ���� sector ��
;-----------------------------------------------
%macro LBA_TO_CHS 1
        mov ax, %1                      ; paramter
        mov cl, SPT
        div cl                          ; al = LBA / SPT, ah = LBA % SPT        
; cylinder = LBA / SPT / HPC
        mov ch, al
        shr ch, (HPC / 2)               ; ch = cylinder                
; head = (LBA / SPT ) % HPC
        mov dh, al
        and dh, 1                       ; dh = head
; sector = LBA % SPT + 1
        mov cl, ah
        inc cl                          ; cl = sector
%endmacro



%endif