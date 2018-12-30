class Cube {

  // Attributes
  float [] center;   // the coordinates of the center of the 3 dimensional shape
  float [][] vertices; // the coordinates of the shape's vertices
  float cubeHeight; // the shape's height
  float cubeWidth; // the shape's length
  float cubeDepth;   // the shape's depth
  // polar coordinates
  float psi;   // yaw angle
  float theta; // pitch angle
  float phi;   // roll angle
  // view
  String view = "top"; // default top.
  
  // member functions
  
  // default constructor
  Cube() {
    // initialize center array to be at the top left corner of the canvas
    center = new float [3];
    updateCenter(0,0,0);
    
    // initialize dimensions
    cubeHeight  = 50;
    cubeWidth   = 100;
    cubeDepth   = 100;
    
    // initialize attitude
    psi = 0;
    theta = 0;
    phi = 0;
    
    // update vertices
    initializeVertices();
  } // end constructor
  
  void updateCenter(float x, float y, float z){
    center[0] = x;
    center[1] = y;
    center[2] = z;
  }
  
  void updateAttitude(float yaw, float pitch, float roll){
    psi = -yaw;
    theta = pitch;
    phi = -roll;
  }
  
  // function calculates and updates each vertex position with respect to the shape's center.
  void initializeVertices(){
     // initialize vertices position coordinates with respect to shape's center
    vertices = new float[8][3];
    // top-front-left
    vertices[0][0] = cubeDepth/2;  // x-coordinate
    vertices[0][1] = -cubeWidth/2;  // y-coordinate
    vertices[0][2] = -cubeHeight/2; // z-coordinate
    // top-front-right
    vertices[1][0] = cubeDepth/2;  // x-coordinate
    vertices[1][1] = cubeWidth/2;  // y-coordinate
    vertices[1][2] = -cubeHeight/2; // z-coordinate
    // bottom-front-right
    vertices[2][0] = cubeDepth/2;  // x-coordinate
    vertices[2][1] = cubeWidth/2;  // y-coordinate
    vertices[2][2] = cubeHeight/2; // z-coordinate
    // bottom-front-left
    vertices[3][0] = cubeDepth/2;  // x-coordinate
    vertices[3][1] = -cubeWidth/2;  // y-coordinate
    vertices[3][2] = cubeHeight/2; // z-coordinate
    // top-back-left
    vertices[4][0] = -cubeDepth/2;  // x-coordinate
    vertices[4][1] = -cubeWidth/2;  // y-coordinate
    vertices[4][2] = -cubeHeight/2; // z-coordinate
    // top-back-right
    vertices[5][0] = -cubeDepth/2;  // x-coordinate
    vertices[5][1] = cubeWidth/2;  // y-coordinate
    vertices[5][2] = -cubeHeight/2; // z-coordinate
    // bottom-back-right
    vertices[6][0] = -cubeDepth/2;  // x-coordinate
    vertices[6][1] = cubeWidth/2;  // y-coordinate
    vertices[6][2] = cubeHeight/2; // z-coordinate
    // bottom-back-left
    vertices[7][0] = -cubeDepth/2;  // x-coordinate
    vertices[7][1] = -cubeWidth/2;  // y-coordinate
    vertices[7][2] = cubeHeight/2; // z-coordinate
  }
  
  float [][] rotate(float yaw, float pitch, float roll, float [][] vert)
  {
    // For reference only, these are the three matrices used to derive the general rotation matrix below
    ///////////////////////////////////////
    /*
    // yaw rotation matrix
    float [][] yawMatrix = {
      {cos(psi),-sin(psi),0},
      {sin(psi),cos(psi),0},
      {0,0,1}
    };
    
    // pitch rotation matrix
    float [][] pitchMatrix = {
      {1,1,1},
      {1,cos(theta),-sin(theta)},
      {1,sin(theta),cos(theta)}
    };
    
    // roll rotation matrix
    float [][] rollMatrix = {
      {cos(phi),1,sin(phi)},
      {1,1,1},
      {-sin(phi),1,cos(phi)}
    };
    */
    ///////////////////////////////////////
    
    float [][] tempVert = new float [vertices.length][vertices[0].length];
    
    // Transformation matrix for yaw, pitch, and roll
    float [][] rotationMatrix = {
      {cos(yaw)*cos(roll)-sin(yaw)*sin(pitch)*sin(roll), -sin(yaw)*cos(pitch), cos(yaw)*sin(roll)+sin(yaw)*sin(pitch)*cos(roll)},
      {sin(yaw)*cos(roll)+cos(yaw)*sin(pitch)*sin(roll),  cos(yaw)*cos(pitch), sin(yaw)*sin(roll)-cos(yaw)*sin(pitch)*cos(roll)},
      {-cos(pitch)*sin(roll)                           ,  sin(pitch)         , cos(pitch)*cos(roll)                            }
    };
    
    // left-multiply each vertex position vector by the rotation matrix, and store the resulting vector in the temporary vertex array
    for(int i = 0; i < vertices.length; i++){
      float [] temp = {0,0,0};
      for(int j = 0; j < rotationMatrix.length; j++){
        temp[j] = vert[i][0] * rotationMatrix[j][0] + vert[i][1] * rotationMatrix[j][1] + vert[i][2] * rotationMatrix[j][2]; 
      }
      tempVert[i][0] = temp[0]; // x-coordinate
      tempVert[i][1] = temp[1]; // y-coordinate
      tempVert[i][2] = temp[2]; // z-coordinate
    };
    
    return tempVert;
    
  }
  
  // this function applies transormations to the vertices
  float [][] transformVertices(){
    
    float [][] tempVert = new float [vertices.length][vertices[0].length];
    
    // Rotation based on attitude settings
    tempVert = rotate(psi,theta,phi,vertices);
    
    // Change the coordinate axes based on the view parameter.
    switch(view){
      case "top": 
        // do nothing, it's the default view
        break;
      case "front":
        tempVert = rotate(0,PI/2,0,tempVert);
        break;
      case "rear":
        tempVert = rotate(PI,-PI/2,0,tempVert);
        break;
      case "rightSide":
        tempVert = rotate(-PI/2,0,PI/2,tempVert);
        break;
      case "leftSide":
        tempVert = rotate(PI/2,0,-PI/2,tempVert);
        break;
    }
    
    // return the array that holds the rotated vertices
    return tempVert;
  }
  
  void setView(String s){
    view = s;
  }
  
  String getView(){
    return view;
  }
  
  // this function returns th cube's yaw value
  float getYaw(){
    return -psi;
  }
  
  // this function returns th cube's ypitch value
  float getPitch(){
    return theta;
  }
  
  // this function returns th cube's roll value
  float getRoll(){
    return -phi;
  }
  
  // function draw the vertices on the canvas
  void drawCube(){
    // transforme vertices
    float [][] transformedVertices = transformVertices();
    
    // draw shape
    beginShape(QUADS);
      // bottom
      fill(1,0,0); vertex(center[0]+transformedVertices[0][0],center[1]+transformedVertices[0][1],center[2]+transformedVertices[0][2]);
      fill(1,0,0); vertex(center[0]+transformedVertices[1][0],center[1]+transformedVertices[1][1],center[2]+transformedVertices[1][2]);
      fill(1,0,0); vertex(center[0]+transformedVertices[5][0],center[1]+transformedVertices[5][1],center[2]+transformedVertices[5][2]);
      fill(1,0,0); vertex(center[0]+transformedVertices[4][0],center[1]+transformedVertices[4][1],center[2]+transformedVertices[4][2]);
      // left side
      fill(0,1,0); vertex(center[0]+transformedVertices[0][0],center[1]+transformedVertices[0][1],center[2]+transformedVertices[0][2]);
      fill(0,1,0); vertex(center[0]+transformedVertices[1][0],center[1]+transformedVertices[1][1],center[2]+transformedVertices[1][2]);
      fill(0,1,0); vertex(center[0]+transformedVertices[2][0],center[1]+transformedVertices[2][1],center[2]+transformedVertices[2][2]);
      fill(0,1,0); vertex(center[0]+transformedVertices[3][0],center[1]+transformedVertices[3][1],center[2]+transformedVertices[3][2]);
      // front
      fill(0,0,1); vertex(center[0]+transformedVertices[1][0],center[1]+transformedVertices[1][1],center[2]+transformedVertices[1][2]);
      fill(0,0,1); vertex(center[0]+transformedVertices[5][0],center[1]+transformedVertices[5][1],center[2]+transformedVertices[5][2]);
      fill(0,0,1); vertex(center[0]+transformedVertices[6][0],center[1]+transformedVertices[6][1],center[2]+transformedVertices[6][2]);
      fill(0,0,1); vertex(center[0]+transformedVertices[2][0],center[1]+transformedVertices[2][1],center[2]+transformedVertices[2][2]);
      // right side
      fill(1,1,1); vertex(center[0]+transformedVertices[4][0],center[1]+transformedVertices[4][1],center[2]+transformedVertices[4][2]);
      fill(1,1,1); vertex(center[0]+transformedVertices[5][0],center[1]+transformedVertices[5][1],center[2]+transformedVertices[5][2]);
      fill(1,1,1); vertex(center[0]+transformedVertices[6][0],center[1]+transformedVertices[6][1],center[2]+transformedVertices[6][2]);
      fill(1,1,1); vertex(center[0]+transformedVertices[7][0],center[1]+transformedVertices[7][1],center[2]+transformedVertices[7][2]);
      // rear
      fill(1,1,0); vertex(center[0]+transformedVertices[0][0],center[1]+transformedVertices[0][1],center[2]+transformedVertices[0][2]);
      fill(1,1,0); vertex(center[0]+transformedVertices[4][0],center[1]+transformedVertices[4][1],center[2]+transformedVertices[4][2]);
      fill(1,1,0); vertex(center[0]+transformedVertices[7][0],center[1]+transformedVertices[7][1],center[2]+transformedVertices[7][2]);
      fill(1,1,0); vertex(center[0]+transformedVertices[3][0],center[1]+transformedVertices[3][1],center[2]+transformedVertices[3][2]);
      // top
      fill(0,1,1); vertex(center[0]+transformedVertices[3][0],center[1]+transformedVertices[3][1],center[2]+transformedVertices[3][2]);
      fill(0,1,1); vertex(center[0]+transformedVertices[2][0],center[1]+transformedVertices[2][1],center[2]+transformedVertices[2][2]);
      fill(0,1,1); vertex(center[0]+transformedVertices[6][0],center[1]+transformedVertices[6][1],center[2]+transformedVertices[6][2]);
      fill(0,1,1); vertex(center[0]+transformedVertices[7][0],center[1]+transformedVertices[7][1],center[2]+transformedVertices[7][2]); 
    endShape();
  } // end drawCube
  
  void drawAxes(){
    // draw axes
    stroke(1,1,1);
    line(100,100,0,100,200,0);
    line(100,100,0,200,100,0);
    line(100,100,0,50,150,0);
    
    // draw labels
    String [] labels = new String [3];
    if(view == "top"){
      labels[0] = "-X";
      labels[1] = "Y";
      labels[2] = "Z";
    } else if(view == "front"){
      labels[0] = "-X";
      labels[1] = "-Z";
      labels[2] = "Y";
    } else if(view == "rear"){
      labels[0] = "X";
      labels[1] = "-Z";
      labels[2] = "-Y";
    } else if(view == "rightSide"){
      labels[0] = "Y";
      labels[1] = "-Z";
      labels[2] = "X";
    } else if(view == "leftSide"){
      labels[0] = "-Y";
      labels[1] = "-Z";
      labels[2] = "-X";
    }
    
    fill(1,1,1);
    textSize(15);
    text(labels[0],215,100);
    text(labels[1],100,215);
    text(labels[2],38,165);
  }
  
}