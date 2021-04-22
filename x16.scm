(define memories
  '((memory program
            (address (#x801 . #x6fff))
            (section (programStart #x801)
                     code switch data cdata izpage data_init_table))
    (memory zeroPage
            (address (#x2 . #x7f))
            (section registers zzpage zpage))
    (memory zeroPage2
            (address (#xa9 . #xf7f))
            (section registers))
    (memory low
            (address (#x400 . #x7ff))
            (section zdata))
    (memory data
            (address (#x7000 . #x9eff))
            (section zdata cstack heap))
    (block cstack (size #x800))               ; C stack size
    (block heap   (size #x800))               ; heap size
    ))
