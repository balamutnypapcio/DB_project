include("/home/jakub/Projekty/DB/bazy_danych_v3/build/Desktop_Qt_6_9_0-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/bazy_danych_v3-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/jakub/Projekty/DB/bazy_danych_v3/build/Desktop_Qt_6_9_0-Debug/bazy_danych_v3
    GENERATE_QT_CONF
)
