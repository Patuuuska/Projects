package com.example.model;

public class Rating {

    private String groupId;
    private int score;

    public Rating() {
    }

    public Rating(String groupId, int score) {
        this.groupId = groupId;
        this.score = score;
    }

    public String getGroupId() {
        return groupId;
    }

    public void setGroupId(String groupId) {
        this.groupId = groupId;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }
}
