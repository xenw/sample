; pci.inc
; Copyright (c) 2009-2012 mik 
; All rights reserved.


; ���ģ���ǹ��� PCI ��һЩ��

%ifndef PIC_INC
%define PIC_INC

%include "ports.inc"


; ���� PCI �ռ䳣��
%define PCI_FEC00000            0x600000





;--------------------------------------------
; MAKE_PCI_ADDRESS(): �ϳ�һ�� PCI ��ַ���� eax �Ĵ���
; args: 
;	bus, device, function, offset
;---------------------------------------------
%macro MAKE_PCI_ADDRESS 4
	mov eax, DWORD (0x80000000|(%1<<16)|(%2<<11)|(%3<<8)|(%4&0xfc))
%endmacro



;---------------------------------------------
; READ_PCI_DWORD(): ��һ��DWORD
; args:
;	bus, device, function, offset
;----------------------------------------------
%macro READ_PCI_DWORD 4
	mov dx, CONFIG_ADDRESS
	MAKE_PCI_ADDRESS %1, %2, %3, %4
	out dx, eax
	mov dx, CONFIG_DATA
	in eax, dx
%endmacro


;---------------------------------------------
; READ_PCI_WORD(): ��һ��WORD
; args:
;	bus, device, function, offset
;----------------------------------------------
%macro READ_PCI_WORD 4
	mov dx, CONFIG_ADDRESS
	MAKE_PCI_ADDRESS %1, %2, %3, %4
	out dx, eax
	mov dx, CONFIG_DATA
	in ax, dx
%endmacro


;---------------------------------------------
; READ_PCI_BYTE(): ��һ�� BYTE
; args:
;	bus, device, function, offset
;----------------------------------------------
%macro READ_PCI_BYTE 4
	mov dx, CONFIG_ADDRESS
	MAKE_PCI_ADDRESS %1, %2, %3, %4
	out dx, eax
	mov dx, CONFIG_DATA
	in al, dx
%endmacro



;---------------------------------------------
; WRITE_PCI_DWORD(): дһ�� DWORD
; args:
;	bus, device, function, offset, value
;----------------------------------------------
%macro WRITE_PCI_DWORD 5
	mov dx, CONFIG_ADDRESS
	MAKE_PCI_ADDRESS %1, %2, %3, %4
	out dx, eax
	mov dx, CONFIG_DATA
	mov eax, %5
	out dx, eax
%endmacro


;---------------------------------------------
; WRITE_PCI_WORD(): дһ�� WORD
; args:
;	bus, device, function, offset, value
;----------------------------------------------
%macro WRITE_PCI_WORD 5
	mov dx, CONFIG_ADDRESS
	MAKE_PCI_ADDRESS %1, %2, %3, %4
	out dx, eax
	mov dx, CONFIG_DATA
	mov ax, %5
	out dx, ax
%endmacro


;---------------------------------------------
; WRITE_PCI_BYTE(): дһ�� BYTE
; args:
;	bus, device, function, offset, value
;----------------------------------------------
%macro WRITE_PCI_BYTE 5
	mov dx, CONFIG_ADDRESS
	MAKE_PCI_ADDRESS %1, %2, %3, %4
	out dx, eax
	mov dx, CONFIG_DATA
	mov al, %5
	out dx, al
%endmacro


;-------------------------------------
; DO_SIM(): �������� SMI �ж�
; args:
;	%1: ���͸� SMI handler �Ĳ���
;--------------------------------------
%macro DO_SMI 1
	mov dx, APM_CNT			; advanced power management ���ƼĴ���
	mov al, %1
	out dx, al			; ���� SMI �ж�
%endmacro

;-------------------------------------
; DO_SIM(): �������� SMI �ж�
; args:
;	%1: ���͸� SMI handler �Ĳ���
;--------------------------------------
%macro DO_SMI 0
	mov dx, APM_CNT			; advanced power management ���ƼĴ���
	mov al, 0
	out dx, al			; ���� SMI �ж�
%endmacro



;---------------------------------
; DO_NMI(): �������� #NMI �ж�
;---------------------------------
%macro DO_NMI 0
	call get_TCOBASE
	lea edx, [eax + 08h]		; TCO1 control
	in ax, dx
	or ax, 100h			; NMI NOW 
	out dx, ax
%endmacro	

%define CLEAR_NMI	DO_NMI



;-----------------------------------------------
; SMRAM_OPEN() �� SMRAM �ɶ�
; ������
;	ʹ�� compatible SMM space ������ DRAM
;-----------------------------------------------
%macro SMRAM_OPEN 0
	READ_PCI_DWORD 0, 0, 0, 9Dh
	or eax, 4800h			; D_OPEN=1, G_SMRARE=1
	mov ebx, eax
	WRITE_PCI_DWORD 0, 0, 0, 9Dh, ebx
%endmacro

;-----------------------------------------------
; SMRAM_OPEN() �ر� SMRAM
; ������
;	ʹ�� compatible SMM space ������ VGA
;-----------------------------------------------
%macro SMRAM_CLOSE 0
	READ_PCI_DWORD 0, 0, 0, 9Dh
	btr eax, 14			; D_OPEN=0
	bts eax, 13			; D_CLS=1
	mov ebx, eax
	WRITE_PCI_DWORD 0, 0, 0, 9Dh, ebx
%endmacro


;----------------------------------------------
; SET_SMRAM_OPEN(): ��SMRAM �ɶ�
;----------------------------------------------
%macro SET_SMRAM_OPEN 0
;; Note: only for bochs (440FX chipset)
	MAKE_PCI_ADDRESS	0, 0, 0, 70h
	mov dx, CONFIG_ADDRESS
	out dx, eax
	mov dx, CONFIG_DATA + 2
	mov al, 4Ah				; D_OPEN = 1, D_LCK = 0
	out dx, al
%endmacro

;----------------------------------------------
; SET_SMRAM_CLOSE(): �ر� SMRAM �ɶ�
;----------------------------------------------
%macro SET_SMRAM_CLOSE 0
;; Note: only for bochs (440FX chipset)
	MAKE_PCI_ADDRESS	0, 0, 0, 70h
	mov dx, CONFIG_ADDRESS
	out dx, eax
	mov dx, CONFIG_DATA + 2
	mov al, 0Ah				; D_OPEN = 0
	out dx, al
%endmacro
	
	
	
%endif
