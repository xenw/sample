; module.inc
; Copyright (c) 2009-2013 mik 
; All rights reserved.


%ifndef __MODULE_INC__
%define __MODULE_INC__


;---------------------------------------------------------------------------
; �� MODULE_HEADER: ����ģ��ͷ�ṹ
; input:
;       $1 - ģ�� size
; example:
;       MODULE_HEADER   1, (PROECTED_END - PROTECTED_BEGIN)
; explain:
;       ���� protected ģ��ͷ�ṹ����СΪ �� PROTECTED_END - PROTECTED_BEGIN
;       λ�� disk ������ 1 ��
;----------------------------------------------------------------------------
%macro MODULE_HEADER    1
header_size:            DW      8h              ; MODULE_HEADER �ṹ 6 bytes
sector_position:        DW      $1              ; ģ���� disk ������λ��
module_size:            DD      $2              ; ģ���С
%endmacro



%endif