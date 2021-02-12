// These should be moved:
veraAddress:  .equlab 0x9f20
data0:        .equlab 0x9f23

;;; **********************************************************************
;;;
;;; plot1_320 - set a single pp1 point in a Vera lores bitmap
;;;
;;; Note: This function assumes that port 0 is the active port and
;;;       no increment is used.
;;;
;;; Execution time 129 cycles or 0.0161ms @ 8Mhz
;;;
;;; In: _Zp[1:0] - x coordinate
;;;     _Zp[3:2] - y coordinate
;;;     bitmapStart[3:0] - start address of bitmap
;;; Out: Nothing
;;; Uses: _Zp[5:4], A, X, flags
;;;
;;; **********************************************************************

              .public plot1_320
              .extern _Zp, bitmapStart
plot1_320:    lda     zp:_Zp+2      ; * 256
              sta     zp:_Zp+5
              lsr     zp:_Zp+3      ; * 64
              ror     a
              lsr     zp:_Zp+3
              ror     a
              sta     zp:_Zp+4
              clc
              lda     zp:_Zp+3
              adc     zp:_Zp+5
              sta     zp:_Zp+5      ; zp4_16 = 320 * y

              lda     zp:_Zp+0      ; x >> 3
              lsr     zp:_Zp+1
              ror     a
              lsr     zp:_Zp+1
              ror     a
              lsr     zp:_Zp+1
              ror     a

              clc                   ; zp4_16 = y * 320 + (x >> 3)
              adc     zp:_Zp+4
              sta     zp:_Zp+4
              lda     zp:_Zp+1
              adc     zp:_Zp+5
              sta     zp:_Zp+5

              lda     zp:_Zp+4      ; set pointer to address in Vera memory
              adc     zp:bitmapStart
              sta     veraAddress
              lda     zp:_Zp+5
              adc     zp:bitmapStart+1
              sta     veraAddress+1
              lda     #0
              adc     zp:bitmapStart+2
              sta     veraAddress+2

              lda     zp:_Zp+0      ; set pixel
              and     #7            ; x & 7
              tax
              lda     bitmask_pp1,x
              ora     data0
              sta     data0
              rts

bitmask_pp1:  .byte   1,2,4,8,16,32,64,128
