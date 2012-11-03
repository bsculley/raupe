/*
 * Copyright (C) 2011 Google Inc.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

package de.europa4.android;

import android.app.Activity;
import android.hardware.Camera;
import android.os.Bundle;
import android.view.Window;
import android.widget.TextView;

import org.ros.android.bluecam.BitmapFromCompressedImage;
import org.ros.android.bluecam.R;
import org.ros.android.view.RosImageView;
import org.ros.android.view.camera.RosCameraPreviewView;

/**
 * @author ethan.rublee@gmail.com (Ethan Rublee)
 * @author damonkohler@google.com (Damon Kohler)
 */
public class CamRxActivity extends Activity {

  private int cameraId;
//  private RosCameraPreviewView rosCameraPreviewView;
  private RosImageView<sensor_msgs.CompressedImage> image;
  
  // Key names received from the BluetoothChatService Handler
  public static final String DEVICE_NAME = "device_name";
  public static final String TOAST = "toast";

  // Layout Views
  private TextView mTitle;
  public CamRxActivity() {
//    super("CamRx", "CamRx");
  }

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
    setContentView(R.layout.camrx);
    getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.custom_title);
    
    // Set up the custom title
    mTitle = (TextView) findViewById(R.id.title_left_text);
    mTitle.setText(R.string.app_name);
    mTitle = (TextView) findViewById(R.id.title_right_text);
/*    
    rosCameraPreviewView = (RosCameraPreviewView) findViewById(R.id.ros_camera_preview_view);
    cameraId = 0;
    Camera camera = Camera.open(cameraId);
    rosCameraPreviewView.setCamera(camera);
*/
    image = (RosImageView<sensor_msgs.CompressedImage>) findViewById(R.id.ros_image_view);
    image.setTopicName("/camera/image/compressed");
    image.setMessageType(sensor_msgs.CompressedImage._TYPE);
    image.setMessageToBitmapCallable(new BitmapFromCompressedImage());
//    rosImageView.setMessageType("sensor_msgs/CompressedImage");
    
//	MainActivity.getMainExecutor().execute(rosCameraPreviewView, MainActivity.getNodeConfig());
	MainActivity.getMainExecutor().execute(image, MainActivity.getNodeConfig());
  }

}
