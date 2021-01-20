#include <ros.h>
#include <mcp_can.h>
#include <ros2can/ros2can_message.h>
#include <ros2can/get_data.h>

MCP_CAN CAN(53);

typedef ros::NodeHandle_<ArduinoHardware,25,25,2048,2048> NodeHandle;
NodeHandle nh;

void message_sub_cb(const ros2can::ros2can_message& data);
ros::Subscriber<ros2can::ros2can_message> msg_sub("/tractor/ros2can/write_message_buffer", &message_sub_cb);

ros2can::ros2can_message pub_msg;
ros::Publisher msg_pub("/tractor/ros2can/read_message_buffer", &pub_msg);
unsigned long id = 0;
unsigned long max_id = 40;
void setup()
{
    CAN.begin(CAN_1000KBPS);
    nh.getHardware()->setBaud(57600);
    nh.initNode();
    nh.advertise(msg_pub);
    nh.subscribe(msg_sub);    
    while (!nh.connected()) nh.spinOnce();
    
}




void loop()
{   

    
    if (id == max_id)
    {
      id = 0;
    }
    unsigned char len = 0;
    unsigned char buf[8];
    CAN.init_Filt(0,8,id);
    CAN.readMsgBuf(&len, buf);
    pub_msg.id = id;
    pub_msg.data_1 = buf[0];
    pub_msg.data_2 = buf[1];
    pub_msg.data_3 = buf[2];
    pub_msg.data_4 = buf[3];
    pub_msg.data_5 = buf[4];
    pub_msg.data_6 = buf[5];
    pub_msg.data_7 = buf[6];
    pub_msg.data_8 = buf[7];    
    msg_pub.publish(&pub_msg);
    id++;
    nh.spinOnce();   
}


void message_sub_cb(const ros2can::ros2can_message& data)
{
    byte msg_buf[8];
    msg_buf[0] = data.data_1;
    msg_buf[1] = data.data_2;
    msg_buf[2] = data.data_3;
    msg_buf[3] = data.data_4;
    msg_buf[4] = data.data_5;
    msg_buf[5] = data.data_6;
    msg_buf[6] = data.data_7;
    msg_buf[7] = data.data_8;
    CAN.sendMsgBuf(data.id, 0, 8, msg_buf);
}

void read()
{
    
}
