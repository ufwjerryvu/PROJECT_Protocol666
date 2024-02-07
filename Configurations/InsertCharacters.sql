-- NOTE: this file is to insert Character data into Setup.sql
INSERT INTO CharacterSpawns (level_id, x, y, type, facing, run_speed, jump_velocity, grav_accel, terminal_velocity) 
VALUES
(1, 50, 50, 'MeleeGoon', 0, 4, 8, 2, 12),
(1, 50, 50, 'MeleeGoon', 0, 4, 8, 2, 12),
(1, 50, 50, 'RangedGoon', 0, 4, 8, 2, 12);


INSERT INTO CharacterAnimations (type, action, index, path) 
VALUES 
('Player', 'Idle', 1, '../Assets/Sprite/Character/Player/Ragdoll/idle1.png'),
('Player', 'Idle', 2, '../Assets/Sprite/Character/Player/Ragdoll/idle2.png'),
('Player', 'Idle', 3, '../Assets/Sprite/Character/Player/Ragdoll/idle3.png'),
('Player', 'Idle', 4, '../Assets/Sprite/Character/Player/Ragdoll/idle4.png'),

('Player', 'IdleShoot', 1, '../Assets/Sprite/Character/Player/Ragdoll/idle_shoot1.png'),
('Player', 'IdleShoot', 2, '../Assets/Sprite/Character/Player/Ragdoll/idle_shoot2.png'),

('Player', 'Run', 1, '../Assets/Sprite/Character/Player/Ragdoll/run1.png'),
('Player', 'Run', 2, '../Assets/Sprite/Character/Player/Ragdoll/run2.png'),
('Player', 'Run', 3, '../Assets/Sprite/Character/Player/Ragdoll/run3.png'),
('Player', 'Run', 4, '../Assets/Sprite/Character/Player/Ragdoll/run4.png'),
('Player', 'Run', 5, '../Assets/Sprite/Character/Player/Ragdoll/run5.png'),
('Player', 'Run', 6, '../Assets/Sprite/Character/Player/Ragdoll/run6.png'),
('Player', 'Run', 7, '../Assets/Sprite/Character/Player/Ragdoll/run7.png'),
('Player', 'Run', 8, '../Assets/Sprite/Character/Player/Ragdoll/run8.png'),

('Player', 'RunShoot', 1, '../Assets/Sprite/Character/Player/Ragdoll/run_shoot1.png'),
('Player', 'RunShoot', 2, '../Assets/Sprite/Character/Player/Ragdoll/run_shoot2.png'),
('Player', 'RunShoot', 3, '../Assets/Sprite/Character/Player/Ragdoll/run_shoot3.png'),
('Player', 'RunShoot', 4, '../Assets/Sprite/Character/Player/Ragdoll/run_shoot4.png'),
('Player', 'RunShoot', 5, '../Assets/Sprite/Character/Player/Ragdoll/run_shoot5.png'),
('Player', 'RunShoot', 6, '../Assets/Sprite/Character/Player/Ragdoll/run_shoot6.png'),
('Player', 'RunShoot', 7, '../Assets/Sprite/Character/Player/Ragdoll/run_shoot7.png'),
('Player', 'RunShoot', 8, '../Assets/Sprite/Character/Player/Ragdoll/run_shoot8.png'),

('Player', 'Jump', 1, '../Assets/Sprite/Character/Player/Ragdoll/jump.png'),
('Player', 'Fall', 1, '../Assets/Sprite/Character/Player/Ragdoll/fall.png'),
('Player', 'JumpShoot', 1, '../Assets/Sprite/Character/Player/Ragdoll/jump_shoot1.png'),
('Player', 'JumpShoot', 2, '../Assets/Sprite/Character/Player/Ragdoll/jump_shoot2.png'),
('Player', 'FallShoot', 1, '../Assets/Sprite/Character/Player/Ragdoll/fall_shoot1.png'),
('Player', 'FallShoot', 2, '../Assets/Sprite/Character/Player/Ragdoll/fall_shoot2.png'),

('Player', 'Roll', 1, '../Assets/Sprite/Character/Player/Ragdoll/roll1.png'),
('Player', 'Roll', 2, '../Assets/Sprite/Character/Player/Ragdoll/roll2.png'),
('Player', 'Roll', 3, '../Assets/Sprite/Character/Player/Ragdoll/roll3.png'),
('Player', 'Roll', 4, '../Assets/Sprite/Character/Player/Ragdoll/roll4.png'),
('Player', 'Roll', 5, '../Assets/Sprite/Character/Player/Ragdoll/roll5.png'),
('Player', 'Roll', 6, '../Assets/Sprite/Character/Player/Ragdoll/roll6.png'),
('Player', 'Roll', 7, '../Assets/Sprite/Character/Player/Ragdoll/roll7.png'),
('Player', 'Roll', 8, '../Assets/Sprite/Character/Player/Ragdoll/roll8.png'),

('Player', 'Knockback', 1, '../Assets/Sprite/Character/Player/Ragdoll/knockback.png'),

('MeleeGoon', 'Run', 1, '../Assets/Sprite/Character/Enemy/MeleeGoon/run1.png'),
('MeleeGoon', 'Run', 2, '../Assets/Sprite/Character/Enemy/MeleeGoon/run2.png'),
('MeleeGoon', 'Run', 3, '../Assets/Sprite/Character/Enemy/MeleeGoon/run3.png'),
('MeleeGoon', 'Run', 4, '../Assets/Sprite/Character/Enemy/MeleeGoon/run4.png'),
('MeleeGoon', 'Run', 5, '../Assets/Sprite/Character/Enemy/MeleeGoon/run5.png'),
('MeleeGoon', 'Run', 6, '../Assets/Sprite/Character/Enemy/MeleeGoon/run6.png'),
('MeleeGoon', 'Run', 7, '../Assets/Sprite/Character/Enemy/MeleeGoon/run7.png'),
('MeleeGoon', 'Run', 8, '../Assets/Sprite/Character/Enemy/MeleeGoon/run8.png'),

('MeleeGoon', 'Idle', 1, '../Assets/Sprite/Character/Enemy/MeleeGoon/idle1.png'),
('MeleeGoon', 'Idle', 2, '../Assets/Sprite/Character/Enemy/MeleeGoon/idle2.png'),
('MeleeGoon', 'Idle', 3, '../Assets/Sprite/Character/Enemy/MeleeGoon/idle3.png'),
('MeleeGoon', 'Idle', 4, '../Assets/Sprite/Character/Enemy/MeleeGoon/idle4.png'),

('MeleeGoon', 'Jump', 1, '../Assets/Sprite/Character/Enemy/MeleeGoon/jump.png'),
('MeleeGoon', 'Fall', 1, '../Assets/Sprite/Character/Enemy/MeleeGoon/fall.png'),
('MeleeGoon', 'Knockback', 1, '../Assets/Sprite/Character/Enemy/MeleeGoon/knockback.png'),

('RangedGoon', 'Idle', 1, '../Assets/Sprite/Character/Enemy/RangedGoon/idle1.png'),
('RangedGoon', 'Idle', 2, '../Assets/Sprite/Character/Enemy/RangedGoon/idle2.png'),
('RangedGoon', 'Idle', 3, '../Assets/Sprite/Character/Enemy/RangedGoon/idle3.png'),
('RangedGoon', 'Idle', 4, '../Assets/Sprite/Character/Enemy/RangedGoon/idle4.png'),

('RangedGoon', 'IdleShoot', 1, '../Assets/Sprite/Character/Enemy/RangedGoon/idle_shoot1.png'),
('RangedGoon', 'IdleShoot', 2, '../Assets/Sprite/Character/Enemy/RangedGoon/idle_shoot2.png'),

('RangedGoon', 'Run', 1, '../Assets/Sprite/Character/Enemy/RangedGoon/run1.png'),
('RangedGoon', 'Run', 2, '../Assets/Sprite/Character/Enemy/RangedGoon/run2.png'),
('RangedGoon', 'Run', 3, '../Assets/Sprite/Character/Enemy/RangedGoon/run3.png'),
('RangedGoon', 'Run', 4, '../Assets/Sprite/Character/Enemy/RangedGoon/run4.png'),
('RangedGoon', 'Run', 5, '../Assets/Sprite/Character/Enemy/RangedGoon/run5.png'),
('RangedGoon', 'Run', 6, '../Assets/Sprite/Character/Enemy/RangedGoon/run6.png'),
('RangedGoon', 'Run', 7, '../Assets/Sprite/Character/Enemy/RangedGoon/run7.png'),
('RangedGoon', 'Run', 8, '../Assets/Sprite/Character/Enemy/RangedGoon/run8.png'),

('RangedGoon', 'Jump', 1, '../Assets/Sprite/Character/Enemy/RangedGoon/jump.png'),
('RangedGoon', 'Fall', 1, '../Assets/Sprite/Character/Enemy/RangedGoon/fall.png'),
('RangedGoon', 'JumpShoot', 1, '../Assets/Sprite/Character/Enemy/RangedGoon/jump_shoot1.png'),
('RangedGoon', 'JumpShoot', 2, '../Assets/Sprite/Character/Enemy/RangedGoon/jump_shoot2.png'),
('RangedGoon', 'FallShoot', 1, '../Assets/Sprite/Character/Enemy/RangedGoon/fall_shoot1.png'),
('RangedGoon', 'FallShoot', 2, '../Assets/Sprite/Character/Enemy/RangedGoon/fall_shoot2.png'),

('RangedGoon', 'Knockback', 1, '../Assets/Sprite/Character/Enemy/RangedGoon/knockback.png');