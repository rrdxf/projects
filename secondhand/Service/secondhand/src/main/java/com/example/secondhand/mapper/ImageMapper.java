package com.example.secondhand.mapper;


import com.example.secondhand.beans.Image;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

@Mapper
public interface ImageMapper {
    public List<Image> findImage();
    public int inSertImage(Image image);
    public int deletimage(String good_id);
}
