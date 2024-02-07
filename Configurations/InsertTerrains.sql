-- NOTE: this file is to insert Terrain data into Setup.sql
INSERT INTO TerrainSpawns (level_id, x, y, type, width, height) 
VALUES
(1, 220, 470,'HalfSinglePlatform', 6, 0),
(1, 620, 316,'HalfSinglePlatform', 6, 0),
(1, 1020, 450,'HalfSinglePlatform', 6, 0);

INSERT INTO MatrixAssemblies (type, row, column, path)
VALUES
('Ground', 0, 0, '../Assets/Sprite/Terrain/Ground/0_0'),
('Ground', 0, 1, '../Assets/Sprite/Terrain/Ground/0_1'),
('Ground', 0, 2, '../Assets/Sprite/Terrain/Ground/0_2'),
('Ground', 1, 0, '../Assets/Sprite/Terrain/Ground/1_0'),
('Ground', 1, 1, '../Assets/Sprite/Terrain/Ground/1_1'),
('Ground', 1, 2, '../Assets/Sprite/Terrain/Ground/1_2'),
('Ground', 2, 0, '../Assets/Sprite/Terrain/Ground/2_0'),
('Ground', 2, 1, '../Assets/Sprite/Terrain/Ground/2_1'),
('Ground', 2, 2, '../Assets/Sprite/Terrain/Ground/2_2'),

('SinglePlatform', 0, 0, '../Assets/Sprite/Terrain/Platform/SinglePlatform/0_0'),
('SinglePlatform', 0, 1, '../Assets/Sprite/Terrain/Platform/SinglePlatform/0_1'),
('SinglePlatform', 0, 2, '../Assets/Sprite/Terrain/Platform/SinglePlatform/0_2'),

('FullSinglePlatform', 0, 0, '../Assets/Sprite/Terrain/Platform/FullSinglePlatform/0_0'),
('FullSinglePlatform', 0, 1, '../Assets/Sprite/Terrain/Platform/FullSinglePlatform/0_1'),
('FullSinglePlatform', 0, 2, '../Assets/Sprite/Terrain/Platform/FullSinglePlatform/0_2'),

('HalfSinglePlatform', 0, 2, '../Assets/Sprite/Terrain/Platform/HalfSinglePlatform/0_2'),
('HalfSinglePlatform', 0, 1, '../Assets/Sprite/Terrain/Platform/HalfSinglePlatform/0_1'),
('HalfSinglePlatform', 0, 2, '../Assets/Sprite/Terrain/Platform/HalfSinglePlatform/0_2'),

('MultiplePlatform', 0, 0, '../Assets/Sprite/Terrain/Platform/MultiplePlatform/0_0'),
('MultiplePlatform', 0, 1, '../Assets/Sprite/Terrain/Platform/MultiplePlatform/0_1'),
('MultiplePlatform', 0, 2, '../Assets/Sprite/Terrain/Platform/MultiplePlatform/0_2'),
('MultiplePlatform', 1, 0, '../Assets/Sprite/Terrain/Platform/MultiplePlatform/1_0'),
('MultiplePlatform', 1, 1, '../Assets/Sprite/Terrain/Platform/MultiplePlatform/1_1'),
('MultiplePlatform', 1, 2, '../Assets/Sprite/Terrain/Platform/MultiplePlatform/1_2'),
('MultiplePlatform', 2, 0, '../Assets/Sprite/Terrain/Platform/MultiplePlatform/2_0'),
('MultiplePlatform', 2, 1, '../Assets/Sprite/Terrain/Platform/MultiplePlatform/2_1'),
('MultiplePlatform', 2, 2, '../Assets/Sprite/Terrain/Platform/MultiplePlatform/2_2');