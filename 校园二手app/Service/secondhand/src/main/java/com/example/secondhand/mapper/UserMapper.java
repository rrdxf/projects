package com.example.secondhand.mapper;


import com.example.secondhand.beans.User;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

@Mapper
public interface UserMapper {
    int insertUser(User user);
    User findUserById(String Userid,String Userpassword);
    User findifnullbyId(String Userid);

    List<User> selectall();
    int updateIcon(String iconname,String userid);
    int deletuser(String userid);
}
