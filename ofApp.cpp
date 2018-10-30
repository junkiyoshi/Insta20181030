#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	ofIcoSpherePrimitive ico_sphere = ofIcoSpherePrimitive(250, 2);
	vector<ofMeshFace> triangles = ico_sphere.getMesh().getUniqueFaces();
	for (int i = 0; i < triangles.size(); i++) {

		ofPoint average = (triangles[i].getVertex(0) + triangles[i].getVertex(1) + triangles[i].getVertex(2)) / 3;
		this->locations.push_back(average);
	}

	for (int i = 0; i < this->locations.size(); i++) {

		vector<ofPoint> next_point = vector<ofPoint>();
		for (int j = 0; j < this->locations.size(); j++) {

			if (i == j || next_point.size() >= 3) { continue; }

			float distance = this->locations[i].distance(this->locations[j]);
			if (distance < 45) {

				next_point.push_back(this->locations[j]);
			}
		}

		this->next_points.push_back(next_point);
	}

}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int x = -750; x <= 750; x += 750) {

		for (int y = -750; y <= 750; y += 750) {

			ofPushMatrix();
			ofTranslate(x, y);
			ofRotateY(ofGetFrameNum() * 0.5);

			float random_seed = ofRandom(100);
			for (int location_index = 0; location_index < this->locations.size(); location_index++) {

				ofPoint location = this->locations[location_index];
				float location_noise = ofNoise(random_seed, location.x * 0.005, location.y * 0.005, ofGetFrameNum() * 0.005);
				if (location_noise > 0.6) {

					location = location.normalized() * 350;
				}

				for (int next_index = 0; next_index < this->next_points[location_index].size(); next_index++) {

					ofPoint next_point = this->next_points[location_index][next_index];
					float next_noise = ofNoise(random_seed, next_point.x * 0.005, next_point.y * 0.005, ofGetFrameNum() * 0.005);
					if (next_noise > 0.6) {

						next_point = next_point.normalized() * 350;
					}

					ofDrawLine(location, next_point);
				}
			}

			ofPopMatrix();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}