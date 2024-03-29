-- NOTE: this file is to create tables and insert values in tables that contain Parent Keys.
CREATE TABLE IF NOT EXISTS Characters(
    type TEXT PRIMARY KEY
);

CREATE TABLE IF NOT EXISTS Levels (
    level_id INTEGER PRIMARY KEY,
    width INTEGER NOT NULL,
    height INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS CharacterAnimations (
    path TEXT NOT NULL,
    type TEXT NOT NULL,
    action TEXT NOT NULL,
    index INTEGER NOT NULL,
    PRIMARY KEY (type, action, index),
    FOREIGN KEY (type) REFERENCES Characters(type)
);

CREATE TABLE IF NOT EXISTS CharacterSpawns (
    level_id INTEGER NOT NULL,
    x INTEGER NOT NULL,
    y INTEGER NOT NULL,
    PRIMARY KEY (level_id, x, y),
    type TEXT NOT NULL,
    facing TEXT NOT NULL,
    run_speed INTEGER NOT NULL,
    jump_velocity INTEGER NOT NULL,
    grav_accel INTEGER NOT NULL,
    terminal_velocity INTEGER NOT NULL,
    FOREIGN KEY (level_id) REFERENCES Levels(level_id),
    FOREIGN KEY (type) REFERENCES Characters(type)
);

CREATE TABLE IF NOT EXISTS PlayerSpawns (
    level_id INTEGER AUTOINCREMENT,
    x INTEGER NOT NULL,
    y INTEGER NOT NULL,
    facing TEXT NOT NULL,
    roll_speed INTEGER NOT NULL,
    run_speed INTEGER NOT NULL,
    jump_velocity INTEGER NOT NULL,
    grav_accel INTEGER NOT NULL,
    terminal_velocity INTEGER NOT NULL,
    PRIMARY KEY (level_id, x, y),
    FOREIGN KEY (level_id) REFERENCES Levels(level_id)
);

CREATE TABLE IF NOT EXISTS TerrainSpawns (
    level_id INTEGER NOT NULL,
    x INTEGER NOT NULL,
    y INTEGER NOT NULL,
    type TEXT NOT NULL,
    width INTEGER NOT NULL,
    height INTEGER NOT NULL,
    PRIMARY KEY (level_id, x, y),
    FOREIGN KEY (level_id) REFERENCES levels(level_id),
    FOREIGN KEY (type) REFERENCES Terrains(type)
);

CREATE TABLE IF NOT EXISTS Terrains(
    type TEXT PRIMARY KEY
);

CREATE TABLE IF NOT EXISTS MatrixAssemblies (
    type TEXT NOT NULL,
    row INTEGER NOT NULL,
    column INTEGER NOT NULL,
    PRIMARY KEY(type, row, column),
    path TEXT NOT NULL,
    FOREIGN KEY(type) REFERENCES Terrains(type)
);

-- Insert data
INSERT INTO Characters (type) VALUES ('Player'), ('MeleeGoon'), ('RangedGoon');

INSERT INTO Levels (level_id, width, height) VALUES (1, 1500, 800);

INSERT INTO Terrains (type) VALUES ('Ground'), ('FullSinglePlatform'), ('HalfSinglePlatform'),
('MultiplePlatform'), ('SinglePlatform');

INSERT INTO PlayerSpawns (level_id, x, y, facing, roll_speed, run_speed, jump_velocity, grav_accel, terminal_velocity) 
VALUES
(1, 50, 50, 0, 6, 4, 8, 2, 12);