package com.example.service;

import com.example.model.ClassContainer;
import com.example.model.Rating;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Map;

@Service
public class RatingService {

    private final ClassContainer classContainer;

    @Autowired
    public RatingService(ClassContainer classContainer) {
        this.classContainer = classContainer;
    }

    public Rating getRatingByGroupId(String groupId) {
        Map<String, Rating> ratings = classContainer.getRatings();
        return ratings.get(groupId);
    }

    public void addRating(Rating rating) {
        classContainer.getRatings().put(rating.getGroupId(), rating);
    }
}
