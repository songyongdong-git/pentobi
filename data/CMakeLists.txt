if(PENTOBI_BUILD_GUI AND NOT WIN32)

add_custom_target(
  pentobi-64.png ALL
  COMMAND convert ${CMAKE_SOURCE_DIR}/src/pentobi/icons/pentobi-64.svg pentobi-64.png
  DEPENDS ${CMAKE_SOURCE_DIR}/src/pentobi/icons/pentobi-64.svg
  )
add_custom_target(
  application-x-blokus-sgf.png ALL
  COMMAND convert ${CMAKE_CURRENT_SOURCE_DIR}/application-x-blokus-sgf.svg application-x-blokus-sgf.png
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/application-x-blokus-sgf.svg
  )
add_custom_target(
  application-x-blokus-sgf-16.png ALL
  COMMAND convert ${CMAKE_CURRENT_SOURCE_DIR}/application-x-blokus-sgf-16.svg application-x-blokus-sgf-16.png
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/application-x-blokus-sgf-16.svg
  )
add_custom_target(
  application-x-blokus-sgf-32.png ALL
  COMMAND convert ${CMAKE_CURRENT_SOURCE_DIR}/application-x-blokus-sgf-32.svg application-x-blokus-sgf-32.png
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/application-x-blokus-sgf-32.svg
  )
add_custom_target(
  application-x-blokus-sgf-64.png ALL
  COMMAND convert ${CMAKE_CURRENT_SOURCE_DIR}/application-x-blokus-sgf-64.svg application-x-blokus-sgf-64.png
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/application-x-blokus-sgf-64.svg
  )

configure_file(io.sourceforge.pentobi.desktop.in io.sourceforge.pentobi.desktop @ONLY)
configure_file(pentobi.thumbnailer.in pentobi.thumbnailer @ONLY)
configure_file(io.sourceforge.pentobi.appdata.xml.in io.sourceforge.pentobi.appdata.xml @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/src/pentobi/icons/pentobi.png
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/48x48/apps)
install(FILES ${CMAKE_BINARY_DIR}/src/pentobi/icons/pentobi-16.png
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/16x16/apps
  RENAME pentobi.png)
install(FILES ${CMAKE_BINARY_DIR}/src/pentobi/icons/pentobi-32.png
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/32x32/apps
  RENAME pentobi.png)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pentobi-64.png
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/64x64/apps
  RENAME pentobi.png)
install(FILES ${CMAKE_SOURCE_DIR}/src/pentobi/icons/pentobi.svg
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/scalable/apps)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/application-x-blokus-sgf.png
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/48x48/mimetypes)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/application-x-blokus-sgf-16.png
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/16x16/mimetypes
  RENAME application-x-blokus-sgf.png)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/application-x-blokus-sgf-32.png
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/32x32/mimetypes
  RENAME application-x-blokus-sgf.png)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/application-x-blokus-sgf-64.png
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/64x64/mimetypes
  RENAME application-x-blokus-sgf.png)
install(FILES application-x-blokus-sgf.svg
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/scalable/mimetypes)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/io.sourceforge.pentobi.desktop
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pentobi.thumbnailer
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/thumbnailers)
install(FILES pentobi-mime.xml
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/mime/packages)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/io.sourceforge.pentobi.appdata.xml
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/metainfo)

if(PENTOBI_BUILD_KDE_THUMBNAILER)
  configure_file(io.sourceforge.pentobi.kde-thumbnailer.metainfo.xml.in
    io.sourceforge.pentobi.kde-thumbnailer.metainfo.xml @ONLY)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/io.sourceforge.pentobi.kde-thumbnailer.metainfo.xml
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/metainfo)
endif()

endif(PENTOBI_BUILD_GUI AND NOT WIN32)
