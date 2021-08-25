package com.example.secondhand.mapper;

import com.example.secondhand.beans.Admin;
import org.apache.ibatis.annotations.Mapper;

@Mapper
public interface AdminMapper {
    int insertadm(String adminid,String password);
    Admin selectadm(String adminid,String password);
}
