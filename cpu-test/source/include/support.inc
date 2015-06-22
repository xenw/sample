;****************************************************************
;* support.inc                                                  *
;* Copyright (c) 2009-2013 ��־                                 *
;* All rights reserved.                                         *
;****************************************************************



;;
;; �������д�������Ҫ��ͷ�ļ�
;;


%ifndef _SUPPORT_INC
%define _SUPPORT_INC


%include "..\inc\CPU.inc"
%include "..\inc\clib.inc"
%include "..\inc\ports.inc"
%include "..\inc\pci.inc"
%include "..\inc\debug.inc"
%include "..\inc\apic.inc"
%include "..\inc\float.inc"        
%include "..\inc\task.inc"
%include "..\inc\sse.inc"
%include "..\inc\perfmon.inc"
%include "..\inc\page.inc"
%include "..\inc\ioapic.inc"
%include "..\inc\keycode.inc"
%include "..\inc\hpet.inc"
%include "..\inc\vmx.inc"
%include "..\inc\VmxExit.inc"
%include "..\inc\vmcs.inc"
%include "..\inc\VmxVmm.inc"
%include "..\inc\VmxLib.inc"
%include "..\inc\ErrorCode.inc"
%include "..\inc\ScanCode.inc"
%include "..\inc\system_manage_region.inc"
%include "..\inc\LibDef.inc"
%include "..\inc\services.inc"
%include "..\inc\DebugRecord.inc"
%include "..\inc\VmxPage.inc"
%include "..\inc\Decode\Opcode.inc"



;; #
;; # �������ģ����ڴ��
;; #
BOOT_SEGMENT            EQU     7C00h                   ;; boot ģ����ص� 7C00h
SETUP_SEGMENT           EQU     8000h                   ;; setup ģ����ص� 8000h
PROTECTED_SEGMENT       EQU     20000h                  ;; protected ģ����ص� 20000h
LONG_SEGMENT            EQU     20000h                  ;; long ģ����ص� 20000h 
GUEST_BOOT_SEGMENT      EQU     10000h                  ;; guest �� boot ģ����ص� 10000h
GUEST_KERNEL_SEGMENT    EQU     11000h                  ;; guest �� kernel ģ����ص� 11000h




;; #
;; # �������ģ���ӳ���ڵ�λ��
;; #
BOOT_SECTOR             EQU     0                       ;; boot ģ���� 0 ������
SETUP_SECTOR            EQU     1                       ;; setup ģ���� 1 ������
PROTECTED_SECTOR        EQU     64                      ;; protected ģ���� 64 ������
LONG_SECTOR             EQU     256                     ;; long ģ���� 256 ������
GUEST_BOOT_SECTOR       EQU     512                     ;; guest boot ģ���� 512 ������
GUEST_KERNEL_SECTOR     EQU     520                     ;; guest kernel ģ���� 520 ������



;; # 
;; # ������ merge �ϲ����ߵ�����ʾ��
;; # ��������Ĵ��������ṹд��ӳ���ļ�(c.img)
;; 
;; # ..\..\common\boot,0,c.img,63,1                     ## boot д�� c.img �ļ� 63 ������
;; # ..\..\common\setup,0,c.img,1,60                    ## setup д�� c.img �ļ� 1 ������
;; # ..\..\common\long,0,c.img,256,120                  ## long д�� c.img �ļ� 256 ������
;; # ..\..\lib\Guest\GuestBoot,0,c.img,512,2            ## GuestBoot д�� c.img �ļ� 512 ������
;; # ..\..\lib\Guest\GuestKernel,0,c.img,520,20         ## GuestKerenl д�� c.img �ļ� 520 ������


%endif