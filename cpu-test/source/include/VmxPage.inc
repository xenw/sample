;*************************************************
;* VmxPage.inc                                   *
;* Copyright (c) 2009-2013 ��־                  *
;* All rights reserved.                          *
;*************************************************


%ifndef _VMX_PAGE_INC
%define _VMX_PAGE_INC



;;
;; EPT��Extended Page Table��˵����
;; 1) PXT ������SDA.EptPxt
;; 2) PPT ������C0A0_0000h ~ C0BF_FFFFh �� 2M �ռ䣬��Ӧ������ַ A0_0000h ~ BF_FFFFh
;; 3) PDT ���� get_ept_page() ������̬����
;; 4) PT ���� get_ept_page() ������̬����
;;

EPT_PPT_BASE                    EQU     0C0A00000h              ;; EPT PPT �������ַ
EPT_PPT_PHYSICAL_BASE           EQU     0A00000h                ;; EPT PPT ��������ַ

;;
;; �� longmode �£�
;; 1) PXT ������SDA.EptPxt
;; 2) PPT ������FFFF_F800_C0A0_0000h - FFFF_F800_C0BF_FFFFh
;;

EPT_READ                        EQU     1
EPT_WRITE                       EQU     2
EPT_EXECUTE                     EQU     4
EPT_FIXING                      EQU     10000000h
EPT_PS                          EQU     80h
EPT_IPAT                        EQU     40h
EPT_VALID_FLAG                  EQU     800h

;;
;; ���� EPT table entry ���
;;
EPT_PML4E                       EQU     0010000000000000h
EPT_PDPTE                       EQU     0020000000000000h
EPT_PDE                         EQU     0030000000000000h
EPT_PTE                         EQU     0040000000000000h
EPT_LEVEL_MASK                  EQU     0070000000000000h

EPT_PML4E32                     EQU     00100000h
EPT_PDPTE32                     EQU     00200000h
EPT_PDE32                       EQU     00300000h
EPT_PTE32                       EQU     00400000h
EPT_LEVEL_MASK32                EQU     00700000h


EPT_FORCE                       EQU     20000000h
FIX_MISCONF                     EQU     08000000h
FIX_ACCESS                      EQU     04000000h
GET_PTE                         EQU     1 << 24
GET_PAGE_FRAME                  EQU     1 << 25


;;
;; ���� EPT violation ��صĳ���
;;
EPT_VIOLATION_TRANSLATION       EQU     100h                    ;; translation λ��ָʾ�Ƿ��� guest paging-structure�ڷ��� EPT violation



;;
;; ���� EPT misconfiguration �Ķ�����
;;
EPT_MISCONF_NONREADABLE         EQU     10001h                  ;; ���ڲ��ɶ�����
EPT_MISCONF_ONLYEXECUTE         EQU     10002h                  ;; ���� only-execute����VMX��֧�ֶ�����
EPT_MISCONF_RESERVED            EQU     10004h                  ;; ���ڱ���λ��Ϊ0����
EPT_MISCONF_MEMTYPE             EQU     10008h                  ;; ���� memory type ������




DUMP_PAGE_NEST                  EQU     1


;;
;; ���� guest-physical address ӳ���б��ṹ
;;
struc GML
        .GuestPhysicalAddress   RESQ    1                       ;; ��Ҫӳ��� GPA
        .HostPhysicalAddress    RESQ    1                       ;; Ŀ�� HPA
        .EptPageCount           RESD    1                       ;; ҳ������
        .EptPageAttribute       RESD    1                       ;; ҳ������
endstruc


%endif