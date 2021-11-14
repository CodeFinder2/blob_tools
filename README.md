# blob_tools

blob provides a new message type blob/Blob for binary data.

Currently, only [roscpp](http://www.ros.org/wiki/roscpp) is supported.
Other client libraries like [rospy](http://www.ros.org/wiki/rospy) will serialize/deserialize blob data as uint8[],
as defined in the [message definition](https://github.com/meyerj/blob_tools/blob/master/blob/msg/Blob.msg).

This can **also be used to have union-like message fields** where one field of type is `blob/Blob` can be any valid ROS message type (including custom types) and the type must be remembered in an additonal member, e.g.:
```
blob/Blob data # either a 'string' or a 'uint32', stored in 'type'

uint8 type # either TYPE_STRING or TYPE_UINT32
uint8 TYPE_STRING = 1
uint8 TYPE_UINT32 = 2
```

# Usage Example
`MyMessage.msg`:
```
blob/Blob map_blob      # a serialized (and compressed) nav_msgs/OccupancyGridMap
```

Publisher:
```cpp
{
    ...
    MyMessage temp;
    nav_msgs::OccupancyGridMap my_map;
    ...
    temp.map_blob.serialize(my_map);
    temp.map_blob.setCompressed(true); // enable bzip2 compression (apt install libbz2-dev)
    ...
    publisher.publish(temp);
}
```

Subscriber:
```cpp
void callback(const MyMessageConstPtr &msg)
{
    // WARNING: instantiation of the "wrong" data type may result in non-sense data and/or StreamOverrunExceptions
    // blob/Blob is not type-safe!
    nav_msgs::OccupancyGridMapPtr my_map = msg->map_blob.instantiate<nav_msgs::OccupancyGridMap>();

    if (my_map) {
        ....
    }
}
```
