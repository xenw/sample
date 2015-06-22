;************************************************
;* VmxExit.inc                                  *
;* Copyright (c) 2009-2013 ��־                 *
;* All rights reserved.                         *
;************************************************

%ifndef _VMXEXIT_INC
%define _VMXEXIT_INC




;;
;; ������ָ������ VM-exit ����ϸ��Ϣ��
;; 1) INVEPT, INVPCID, INVVPID, VMCLEAR, VMPTRLD, VMPTRST
;;    VMREAD, VMWRITE, VMXON
;; 2) LGDT, SGDT, LIDT, SIDT, LLDT, SLDT, LTR, STR
;; 3) MWAIT
;;
struc INSTRUCTION_INFO
        ;;
        ;; INVLPG ָ��ļ�¼�����Ե�ַ
        ;;
        .LinearAddress:
        
        ;;
        ;; ������ָ���¼�� displacement ֵ
        ;; 1) INVEPT, INVPCID, INVVPID, VMCLEAR, VMPTRLD, VMPTRST
        ;;    VMREAD, VMWRITE, VMXON
        ;; 2) LGDT, SGDT, LIDT, SIDT, LLDT, SLDT, LTR, STR
        ;; 3) MWAIT
        ;;
        .Displacement           RESQ            1


        ;;
        ;; ������ָ���¼�� instruciton length ֵ
        ;; 1) CPUID, GETSEC, INVD, XSETBV, ���� VMX ָ��
        ;; 2) HLT, INVLPG, INVPICD, RDPMC, RDTSC, RDTSCP, RSM
        ;;    MOV-CR3, MOV-CR8, MOV-to-CR0, MOV-to-CR4, MOV-DR
        ;;    CLTS, LMSW, IN/OUT, INS/OUTS, RDMSR, WRMSR, MWAIT
        ;;    MONITOR, PAUSE, LGDT, LIDT, LTR, SGDT, SIDT, SLDT, STR
        ;;    RDRAND, WBINVD
        ;;
        .InstructionLength      RESD            1

        ;;
        ;; ��¼����ָ����ϸ��Ϣ
        ;; 1) INVEPT, INVPCID, INVVPID
        ;; 2) LGDT, LIDT, SGDT, SIDT
        ;; 3) LLDT, SLDT, LTR, STR
        ;; 4) VMCLEAR, VMPTRLD, VMPTRST, VMXON
        ;; 5) VMREAD, WMWRITE
        ;;
        .Flags                  RESD            1
        .Scale                  RESD            1
        .OperandSize            RESD            1       ;; RDRAND ָ���¼������
        .AddressSize            RESD            1
        .Reg1:                                          ;; VMREAD, VMWRITE ָ��� operand 1
        .Register               RESD            1       ;; LLDT, SLDT, LTR, STR ��¼�Ĵ���
        .Segment                RESD            1
        .Index                  RESD            1
        .Base                   RESD            1
        .Reg2:                                          ;; VMREAD, VMWRITE ָ��� operand 2
        .Type                   RESD            1
endstruc

%define INSTRUCTION_FALGS_OPS16         0
%define INSTRUCTION_FALGS_OPS32         (1 << 11)
%define INSTRUCTION_FLAGS_INDEX         (1 << 22)
%define INSTRUCTION_FLAGS_BASE          (1 << 27)
%define INSTRUCTION_FLAGS_REG           (1 << 10)
%define INSTRUCTION_FLAGS_MEM           0
%define SCALE_0                         0
%define SCALE_2                         1
%define SCALE_4                         2
%define SCALE_8                         3
%define INSTRUCTION_OPS_WORD            0
%define INSTRUCTION_OPS_DWORD           1
%define INSTRUCTION_OPS_QWORD           2
%define INSTRUCTION_ADRS_WORD           0
%define INSTRUCTION_ADRS_DWORD          1
%define INSTRUCTION_ADRS_QWORD          2
%define INSTRUCTION_TYPE_SGDT           0
%define INSTRUCTION_TYPE_SIDT           1
%define INSTRUCTION_TYPE_LGDT           2
%define INSTRUCTION_TYPE_LIDT           3
%define INSTRUCTION_TYPE_SLDT           0
%define INSTRUCTION_TYPE_STR            1
%define INSTRUCTION_TYPE_LLDT           2
%define INSTRUCTION_TYPE_LTR            3




;;
;; �쳣�� NMI ���� VM-exit ��ϸ��Ϣ
;;
struc EXCEPTION_INFO
        ;;
        ;; ֱ���쳣/�ж���Ϣ 
        ;;
        .DirectVectorInfo:
        .ExceptionInfo          RESD            1
        .DirectErrorCode:       
        .ExceptionErrorCode     RESD            1
        
        ;;
        ;; ԭʼ�쳣/�ж���Ϣ
        ;;
        .OriginalVectorInfo:
        .IdtVectorInfo          RESD            1
        .OriginalErrorCode:     
        .IdtErrorCode           RESD            1


        ;;
        ;; �� INT3, INTO ָ���¼�� instruction length
        ;;
        .InstructionLength:

        ;;
        ;; �� #PF ��¼�����Ե�ַ
        ;;
        .LinearAddress:

        ;;
        ;; #DB �쳣���¼ BP�� BD�� BS
        ;;
        .BreakPoint             RESD            1
        .DebugFlags             RESD            1
endstruc

%define DEBUG_FLAGS_BD                  (1 << 13)
%define DEBUG_FLAGS_BS                  (1 << 14)





;;
;; �� SIPI ���� VM-exit ����ϸ��Ϣ
;;
struc SIPI_INFO
        .Vector                 RESD            1
endstruc


;;
;; �� SMI ���� VM-exit ����ϸ��Ϣ
;;
struc SMI_INFO
        .OperandSize            RESD            1               ;; ��¼ operand size
        .IoPort                 RESD            1               ;; ��¼�˿�
        .IoFlags                RESD            1               ;; IO ָ���־λ
        
        .Rcx                    RESQ            1
        .Rsi                    RESQ            1
        .Rdi                    RESQ            1
        .Rip                    RESQ            1
endstruc




;;
;; �������л����� VM-exit ����ϸ��Ϣ
;;
struc TASK_SWITCH_INFO
        ;;
        ;; ��ǰ TSS selector ��Ŀ�� TSS selector
        ;;
        .NewTrSelector          RESD            1
        .CurrentTrSelector      RESD            1
        .Source                 RESD            1


        ;;
        ;; ���������������л�ʱ��¼ָ���:
        ;; 1) CALL, JMP, IRET ָ��
        ;; 2) �����ж�/�����쳣 delivery �ڼ�
        ;;
        .InstructionLength      RESD            1

        ALIGNB 8
        ;;
        ;; ��¼��ص�ַ��Ϣ
        ;;
        .GuestGdtBase           RESQ            1
        .GuestLdtBase           RESQ            1
        .GuestIdtBase           RESQ            1
        .CurrentTssDesc         RESQ            1
        .NewTaskTssDesc         RESQ            1
        .CurrentTss             RESQ            1
        .NewTaskTss             RESQ            1

        .GuestGdtLimit          RESD            1
        .GuestIdtLimit          RESD            1

        ;;
        ;; NewTask TSS �ĵ�ֵַ�����Ե�ַ��
        ;;
        .NewTaskTssBase         RESD            1
endstruc

%define TASK_SWITCH_CALL                0
%define TASK_SWITCH_IRET                1
%define TASK_SWITCH_JMP                 2
%define TASK_SWITCH_GATE                3

%define TASK_SWITCH_LOAD_STATE_SUCCESS  0
%define TASK_SWITCH_LOAD_STATE_ERROR    1


;;
;; �жϴ�����Ϣ
;;
struc INTERRUPT_INFO
        .Vector                 RESB            1
        .InterruptType          RESB            1
        .TssSelector            RESW            1
        .TargetSs               RESW            1
        .TargetCs               RESW            1
        .OldSs                  RESW            1
        .OldCs                  RESW            1
        .Cpl                    RESW            1
        .GuestStatus            RESD            1


        ALIGNB 8
        .IdtBase                RESQ            1
        .IdtDesc                RESQ            2
        .GdtBase                RESQ            1
        .TssBase                RESQ            1
        .TssDesc                RESQ            2
        .TargetCsDesc           RESQ            1
        .TargetSsDesc           RESQ            1
        .CurrentSsDesc          RESQ            1

        .Rip                    RESQ            1
        .Rsp                    RESQ            1        
        .TargetRip              RESQ            1
        .TargetRsp              RESQ            1

        .TargetSsLimit          RESD            1
        .TargetCsLimit          RESD            1
        .CurrentSsLimit         RESD            1
   

        .OldFlags               RESD            1
        .OldRip                 RESQ            1
        .OldRsp                 RESQ            1
        .RetRip                 RESQ            1

        INTERRUPT_INFO_SIZE     EQU             $        
endstruc

%define GUEST_STATUS_LONGMODE                   1
%define INTERRUPT_TYPE_NONE                     7
%define INTERRUPT_TYPE_EXTERNAL                 0
%define INTERRUPT_TYPE_SOFTWARE                 4
%define INTERRUPT_TYPE_PRIVILEGE                5
%define INTERRUPT_TYPE_NMI                      2
%define INTERRUPT_TYPE_HARD_EXCEPTION           3
%define INTERRUPT_TYPE_SOFT_EXCEPTION           6




;;
;; �ɿ������������� VM-exit ����ϸ��Ϣ
;;
struc MOV_CR_INFO
        .Type                   RESD            1
        .LmswSource             RESD            1

        ;;
        ;; �Ĵ���ֵ
        ;;
        .ControlRegisterID:
        .ControlRegister        RESQ            1
        .RegisterID:
        .Register               RESQ            1

     
        ;;
        ;; ָ���ַ
        ;;
        .InstructionLength      RESD            1  

        ;;
        ;; ����� LMSW ָ������ VM-exit����¼���Ե�ַ
        ;;
        .LinearAddress          RESQ            1
endstruc

%define CAT_MOV_TO_CR                   0
%define CAT_MOV_FROM_CR                 1
%define CAT_CLTS                        2
%define CAT_LMSW                        3


;;
;; �� MOV-DR ���� VM-exit ����ϸ��Ϣ
;;
struc MOV_DR_INFO
        .DebugRegister          RESD            1
        .Register               RESD            1
        .Direction              RESD            1
        .InstructionLength      RESD            1
endstruc

%define DAT_MOV_TO_DR                   0
%define DAT_MOV_FROM_DR                 1



;;
;; �� I/O ָ������ VM-exit ����ϸ��Ϣ
;;
struc IO_INSTRUCTION_INFO
        .OperandSize            RESD            1               ;; ��¼ operand size
        .IoPort                 RESD            1               ;; ��¼�˿�
        .IoFlags                RESD            1               ;; IO ָ���־λ

        .InstructionLength      RESD            1               ;; ָ���

        ;;
        ;; ����� INS/OUTS ���� VM-exit ʱ��
        ;; 1) ��¼ ES:EDI ���� DS:ESI ���Ե�ַ��
        ;; 2) ��¼ address size
        ;; 3) ��¼ segment
        ;; 4) ��¼ count������ʱ��
        ;;
        .LinearAddress          RESQ            1
        .AddressSize            RESD            1
        .Segment                RESD            1
        .Count                  RESQ            1

        ;;
        ;; ��¼ guest ����д���ֵ
        ;;
        .Value                  RESD            1
endstruc


%define IO_FLAGS_IN                     (1 << 3)
%define IO_FLAGS_OUT                    0
%define IO_FLAGS_STRING                 (1 << 4)
%define IO_FLAGS_REP                    (1 << 5)
%define IO_FLAGS_IMME                   (1 << 6)
%define IO_OPS_BYTE                     0
%define IO_OPS_WORD                     1
%define IO_OPS_DWORD                    3
%define IO_ADRS_WORD                    0
%define IO_ADRS_DWORD                   1
%define IO_ADRS_QWORD                   2
%define SREG_ES                         0
%define SREG_CS                         1
%define SREG_SS                         2
%define SREG_DS                         3
%define SREG_FS                         4
%define SREG_GS                         5


;;
;; APIC-access VM-exit ��ϸ��Ϣ
;;
struc APIC_ACCESS_INFO
        .Offset                 RESD            1
        .Type                   RESD            1
endstruc

%define AAT_LINEAR_READ                 0
%define AAT_LINEAR_WRITE                1
%define AAT_LINEAR_EXECUTE              2
%define AAT_DELIVERY                    3
%define AAT_DELIVERY_GAP                10
%define AAT_GAP                         15



;;
;; EPT violation VM-exit ��ϸ��Ϣ
;;
struc EPT_VIOLAITON_INFO
        .Flags                  RESD            1
        .GuestLinearAddress     RESQ            1
        .GuestPhysicalAddress   RESQ            1
endstruc

%define EPT_FLAGS_READ                  (1 << 1)
%define EPT_FLAGS_WRITE                 (1 << 2)
%define EPT_FLAGS_EXECUTE               (1 << 3)
%define EPT_FLAGS_READABLE              (1 << 4)
%define EPT_FLAGS_WRITEABLE             (1 << 5)
%define EPT_FALGS_EXECUTABLE            (1 << 6)
%define EPT_FLAGS_VALID                 (1 << 7)
%define EPT_FALGS_TRANSLATION           (1 << 8)
%define EPT_NMI_UNBLOCKING              (1 << 12)


;;
;; EPT misconfiguration VM-exit ��ϸ��Ϣ
;;
struc EPT_MISCONF_INFO
        .GuestPhysicalAddress   RESQ            1
endstruc



;;
;; EOI ���⻯ VM-exit ��ϸ��Ϣ
;;
struc EOI_VIRTUALIZATION_INFO
        .Vector                 RESD            1
endstruc



;;
;; APIC-write VM-exit ��ϸ��Ϣ
;;
struc APIC_WRITE_INFO
        .Offset                 RESD            1
endstruc







%endif