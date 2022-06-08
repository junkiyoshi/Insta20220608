#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int x = 160; x < 620; x += 100) {

		for (int y = 160; y < 620; y += 100) {

			ofPushMatrix();
			ofTranslate(x, y);

			ofRotateZ(ofMap(ofNoise(x, y, ofGetFrameNum() * 0.0035), 0, 1, -360, 360));

			auto radius = 40;
			auto deg_start = 0;
			auto deg_end = deg_start + 180;
			auto deg_span = 10;
			for (int deg = deg_start; deg < deg_end; deg += deg_span) {

				auto center = glm::vec2(radius * cos((deg + deg_span / 2) * DEG_TO_RAD), 0);
				auto noise_value = ofNoise((x + center.x) * 0.0075, y * 0.0075, ofGetFrameNum() * 0.01);
				auto rotate = noise_value < 0.5 ? 0.f : ofMap(noise_value, 0.5, 1, 0, 360);

				ofPushMatrix();
				ofTranslate(center);
				ofRotateX(rotate);

				vector<glm::vec2> vertices_1, vertices_2;
				for (int tmp_deg = deg + 1; tmp_deg < deg + deg_span; tmp_deg++) {

					auto point = glm::vec2(radius * cos(tmp_deg * DEG_TO_RAD), radius * sin(tmp_deg * DEG_TO_RAD));
					vertices_1.push_back(point - center);
					vertices_2.push_back(glm::vec2(point.x, -point.y) - center);
				}

				reverse(vertices_2.begin(), vertices_2.end());

				ofFill();
				ofSetColor(0);
				ofBeginShape();
				ofVertices(vertices_1);
				ofVertices(vertices_2);
				ofEndShape(true);

				ofNoFill();
				ofSetColor(255, 0, 0);
				ofBeginShape();
				ofVertices(vertices_1);
				ofVertices(vertices_2);
				ofEndShape(true);

				ofPopMatrix();
			}

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}