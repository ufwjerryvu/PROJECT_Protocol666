-- NOTE: this file is to create tables and insert values.
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
    level_id INTEGER NOT NULL,
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

INSERT INTO CharacterAnimations (type, action, index, path) 
VALUES 
('Player', 'Idle', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/idle1.png'),
('Player', 'Idle', 2, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/idle2.png'),
('Player', 'Idle', 3, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/idle3.png'),
('Player', 'Idle', 4, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/idle4.png'),

('Player', 'IdleShoot', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/idle_shoot1.png'),
('Player', 'IdleShoot', 2, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/idle_shoot2.png'),

('Player', 'Run', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/run1.png'),
('Player', 'Run', 2, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/run2.png'),
('Player', 'Run', 3, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/run3.png'),
('Player', 'Run', 4, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/run4.png'),
('Player', 'Run', 5, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/run5.png'),
('Player', 'Run', 6, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/run6.png'),
('Player', 'Run', 7, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/run7.png'),
('Player', 'Run', 8, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/run8.png'),

('Player', 'RunShoot', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/run_shoot1.png'),
('Player', 'RunShoot', 2, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/run_shoot2.png'),
('Player', 'RunShoot', 3, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/run_shoot3.png'),
('Player', 'RunShoot', 4, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/run_shoot4.png'),
('Player', 'RunShoot', 5, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/run_shoot5.png'),
('Player', 'RunShoot', 6, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/run_shoot6.png'),
('Player', 'RunShoot', 7, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/run_shoot7.png'),
('Player', 'RunShoot', 8, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/run_shoot8.png'),

('Player', 'Jump', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/jump.png'),
('Player', 'Fall', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/fall.png'),
('Player', 'JumpShoot', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/jump_shoot1.png'),
('Player', 'JumpShoot', 2, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/jump_shoot2.png'),
('Player', 'FallShoot', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/fall_shoot1.png'),
('Player', 'FallShoot', 2, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/fall_shoot2.png'),

('Player', 'Roll', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/roll1.png'),
('Player', 'Roll', 2, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/roll2.png'),
('Player', 'Roll', 3, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/roll3.png'),
('Player', 'Roll', 4, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/roll4.png'),
('Player', 'Roll', 5, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/roll5.png'),
('Player', 'Roll', 6, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/roll6.png'),
('Player', 'Roll', 7, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/roll7.png'),
('Player', 'Roll', 8, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/roll8.png'),

('Player', 'Knockback', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Player/Ragdoll/knockback.png'),

('MeleeGoon', 'Run', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/MeleeGoon/run1.png');
('MeleeGoon', 'Run', 2, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/MeleeGoon/run2.png');
('MeleeGoon', 'Run', 3, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/MeleeGoon/run3.png');
('MeleeGoon', 'Run', 4, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/MeleeGoon/run4.png');
('MeleeGoon', 'Run', 5, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/MeleeGoon/run5.png');
('MeleeGoon', 'Run', 6, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/MeleeGoon/run6.png');
('MeleeGoon', 'Run', 7, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/MeleeGoon/run7.png');
('MeleeGoon', 'Run', 8, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/MeleeGoon/run8.png');

('MeleeGoon', 'Idle', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/MeleeGoon/idle1.png');
('MeleeGoon', 'Idle', 2, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/MeleeGoon/idle2.png');
('MeleeGoon', 'Idle', 3, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/MeleeGoon/idle3.png');
('MeleeGoon', 'Idle', 4, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/MeleeGoon/idle4.png');

('MeleeGoon', 'Jump', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/MeleeGoon/jump.png');
('MeleeGoon', 'Fall', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/MeleeGoon/fall.png');
('MeleeGoon', 'Knockback', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/MeleeGoon/knockback.png');

('RangedGoon', 'Idle', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/idle1.png');
('RangedGoon', 'Idle', 2, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/idle2.png');
('RangedGoon', 'Idle', 3, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/idle3.png');
('RangedGoon', 'Idle', 4, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/idle4.png');

('RangedGoon', 'IdleShoot', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/idle_shoot1.png');
('RangedGoon', 'IdleShoot', 2, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/idle_shoot2.png');

('RangedGoon', 'Run', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/run1.png');
('RangedGoon', 'Run', 2, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/run2.png');
('RangedGoon', 'Run', 3, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/run3.png');
('RangedGoon', 'Run', 4, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/run4.png');
('RangedGoon', 'Run', 5, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/run5.png');
('RangedGoon', 'Run', 6, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/run6.png');
('RangedGoon', 'Run', 7, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/run7.png');
('RangedGoon', 'Run', 8, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/run8.png');

('RangedGoon', 'Jump', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/jump.png');
('RangedGoon', 'Fall', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/fall.png');
('RangedGoon', 'JumpShoot', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/jump_shoot1.png');
('RangedGoon', 'JumpShoot', 2, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/jump_shoot2.png');
('RangedGoon', 'FallShoot', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/fall_shoot1.png');
('RangedGoon', 'FallShoot', 2, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/fall_shoot2.png');

('RangedGoon', 'Knockback', 1, '/PROJECT_Protocol666/Assets/Sprite/Character/Enemy/RangedGoon/knockback.png');