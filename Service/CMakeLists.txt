project(Service)

set(LIB_SREVICE_SOURCE ServiceDispatcher.cpp ServiceDispatcher.h Service.h)

add_library(Service ${LIB_SREVICE_SOURCE})