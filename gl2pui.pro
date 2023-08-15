TEMPLATE = app
TARGET   = gl2pui
LIBS += -lglut -lGLEW -lGL

INCLUDEPATH += \
    fnt/ \
    pu/ \
    sg/ \
    ul/

HEADERS += \
    fnt/fnt.h \
    fnt/fntLocal.h \
    pu/pu.h \
    pu/puFLTK.h \
    pu/puGLUT.h \
    pu/puLocal.h \
    pu/puNative.h \
    pu/puPW.h \
    pu/puSDL.h \
    sg/sg.h \
    ul/ul.h \
    ul/ulRTTI.h

SOURCES += \
    fnt/fnt.cxx \
    fnt/fntBitmap.cxx \
    fnt/fntTXF.cxx \
    pu/pu.cxx \
    pu/puArrowButton.cxx \
    pu/puBox.cxx \
    pu/puButton.cxx \
    pu/puButtonBox.cxx \
    pu/puDial.cxx \
    pu/puDialogBox.cxx \
    pu/puFont.cxx \
    pu/puFrame.cxx \
    pu/puGroup.cxx \
    pu/puInput.cxx \
    pu/puInputBase.cxx \
    pu/puInterface.cxx \
    pu/puListBox.cxx \
    pu/puMenuBar.cxx \
    pu/puObject.cxx \
    pu/puOneShot.cxx \
    pu/puPopup.cxx \
    pu/puPopupMenu.cxx \
    pu/puRange.cxx \
    pu/puSlider.cxx \
    pu/puText.cxx \
    pu/puValue.cxx \
    sg/sg.cxx \
    sg/sgd.cxx \
    sg/sgdIsect.cxx \
    sg/sgIsect.cxx \
    sg/sgPerlinNoise.cxx \
    ul/ul.cxx \
    ul/ulError.cxx \
    ul/ulRTTI.cxx \
    main.cpp
