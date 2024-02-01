-- NOTE: this file is to create tables and insert values.

CREATE TABLE IF NOT EXISTS character_animation (
    path TEXT PRIMARY KEY,
    type TEXT NOT NULL,
    action TEXT NOT NULL,
    index INTEGER NOT NULL
    FOREIGN KEY (type) REFERENCES characters(type)
    );

CREATE TABLE IF NOT EXISTS characters (
    id INTEGER PRIMARY KEY,
    type TEXT NOT NULL,
    x INTEGER,
    y INTEGER,
    level_id INTEGER,
    FOREIGN KEY (level_id) REFERENCES levels(level_id)
    );

CREATE TABLE IF NOT EXISTS levels (
    level_id INTEGER PRIMARY KEY,
    width INTEGER NOT NULL,
    height INTEGER NOT NULL
    );

CREATE TABLE IF NOT EXISTS terrain_spawn (
    level_id INTEGER NOT NULL,
    x INTEGER NOT NULL,
    y INTEGER NOT NULL,
    PRIMARY KEY (level_id, x, y)
    type TEXT NOT NULL,
    width INTEGER NOT NULL,
    height INTEGER NOT NULL
    FOREIGN KEY (level_id) REFERENCES levels(level_id)
    );

CREATE TABLE IF NOT EXISTS terrain_assets (
    platform_id INTEGER PRIMARY KEY,
    type TEXT NOT NULL
    );

CREATE TABLE IF NOT EXISTS matrix_assembly (
    path TEXT PRIMARY KEY,
    row INTEGER NOT NULL,
    col INTEGER NOT NULL,
    type TEXT NOT NULL
    );

CREATE TABLE IF NOT EXISTS array_assembly (
    path TEXT PRIMARY KEY,
    index INTEGER NOT NULL,
    type TEXT NOT NULL
    );