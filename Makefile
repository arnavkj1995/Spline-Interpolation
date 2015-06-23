all:
	g++ `pkg-config --cflags opencv` main.cpp splines.cpp `pkg-config --libs opencv` -o sp pose.cpp	alglib/alglibinternal.cpp	alglib/alglibmisc.cpp alglib/ap.cpp  alglib/integration.cpp alglib/interpolation.cpp  alglib/linalg.cpp alglib/optimization.cpp alglib/solvers.cpp alglib/specialfunctions.cpp `pkg-config --libs opencv` -o sp
