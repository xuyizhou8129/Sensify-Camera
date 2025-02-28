#include<iostream>
#include<libcamera/libcamera.h>

using namespace libcamera;
using namespace std;

int main(){
	CameraManager cm;
	cm.start();
	
	if (cm.cameras().empty()){
		cerr << "NO cameras detected!" << endl;
		return -1;
	}
	
	shared_ptr<libcamera::Camera> camera = cm.get(cm.cameras()[0]->id());
	if(!camera){
		cerr <<"Failed to get the camera." << endl;
		cm.stop();
		return -1;
	}
	
	if (camera->acquire()){
		cerr << "Failed to acquire camera" << endl;
		cm.stop();
		return -1;
	}
	
	cout << "Camera acquired:" << camera->id() << endl;
	
	if (camera->stop()){
		cerr << "Failed to stop camera" << endl;
	}
	
	camera->configure(nullptr);
	camera->release();
	cm.stop();
	return 0;

}
