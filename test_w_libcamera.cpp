#include <iostream>
#include <libcamera/libcamera.h>
#include <fstream>

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
	unique_ptr<CameraConfiguration> config = camera->generateConfiguration({StreamRole::VideoRecording});
	
	if (!config || config->size()==0){
		cerr << "Failed to generate camera configuration" << endl;
		camera->release();
		cm.stop();
		return -1;
	}
	
	if (camera->configure(config.get())){
		cerr << "Failed to configure camera" << endl;
		camera->release();
		cm.stop();
		return -1;
	}
	
	Stream *stream = config->at(0).stream();
	unique_ptr<Request> request = camera->createRequest();
	
	FrameBufferAllocator allocator(camera);
	allocator.allocate(stream);
	const vector<unique_ptr<FrameBuffer>> &buffers = allocator.buffers(stream);
	request->addBuffer(stream, buffers[0].get());
	cout << "Waiting for frame ..." << endl;
	FrameBuffer *buffer = request->findBuffer(stream);
	if (buffer) {
		cout << "Frame captured successfully!" << endl;
		ofstream output("captured_image.raw", ios::binary);
		Span<const uint8_t> memory = buffer->planes()[0].mem;
		output.write(reinterpret_cast<const char *>(memory.data()),memory.size());
		output.close();
	}else{
		cerr << "Failed to retrieve frame buffer" << endl;
	}
	
	camera->configure(nullptr);
	camera->release();
	cm.stop();
	return 0;

}
