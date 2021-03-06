BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "album" (
	"a_id"	INTEGER,
	"am_id"	INTEGER NOT NULL,
	"s_id"	INTEGER NOT NULL,
	"b_id"	INTEGER NOT NULL,
	FOREIGN KEY("am_id") REFERENCES "album_matrix"("am_id") ON DELETE CASCADE,
	FOREIGN KEY("s_id") REFERENCES "singles"("s_id"),
	FOREIGN KEY("b_id") REFERENCES "band"("b_id"),
	PRIMARY KEY("am_id","b_id","s_id")
);
CREATE TABLE IF NOT EXISTS "random" (
	"id"	INTEGER NOT NULL
);
CREATE TABLE IF NOT EXISTS "shop_ticket" (
	"st_id"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	"ss_id"	INTEGER NOT NULL,
	"sale_date"	TEXT NOT NULL,
	"unit_price"	REAL NOT NULL,
	"sale_count"	INTEGER NOT NULL DEFAULT 1,
	FOREIGN KEY("ss_id") REFERENCES "shop_stock"("ss_id")
);
CREATE TABLE IF NOT EXISTS "shop_stock" (
	"ss_id"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	"date_load"	TEXT NOT NULL,
	"ar_id"	INTEGER NOT NULL,
	"trade_price"	REAL NOT NULL DEFAULT 1,
	"retail_price"	REAL NOT NULL,
	"total"	INTEGER NOT NULL DEFAULT 0,
	FOREIGN KEY("ar_id") REFERENCES "album_release"("ar_id")
);
CREATE TABLE IF NOT EXISTS "album_release" (
	"ar_id"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	"am_id"	INTEGER NOT NULL,
	"date"	TEXT NOT NULL,
	"cmp_id"	INTEGER NOT NULL,
	FOREIGN KEY("cmp_id") REFERENCES "company"("c_id"),
	FOREIGN KEY("am_id") REFERENCES "album_matrix"("am_id")
);
CREATE TABLE IF NOT EXISTS "album_matrix" (
	"am_id"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	"album_name"	TEXT NOT NULL,
	"cmp_id"	INTEGER NOT NULL,
	FOREIGN KEY("cmp_id") REFERENCES "company"("c_id")
);
CREATE TABLE IF NOT EXISTS "art_band_role" (
	"art_id"	INTEGER NOT NULL,
	"role_id"	INTEGER NOT NULL,
	FOREIGN KEY("role_id") REFERENCES "artist_role"("role_id") ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY("art_id") REFERENCES "artist"("art_id") ON DELETE CASCADE ON UPDATE CASCADE
);
CREATE TABLE IF NOT EXISTS "singles" (
	"s_id"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	"name"	TEXT NOT NULL,
	"author"	INTEGER NOT NULL,
	"history"	TEXT,
	FOREIGN KEY("author") REFERENCES "band"("b_id") ON DELETE CASCADE ON UPDATE CASCADE
);
CREATE TABLE IF NOT EXISTS "artist" (
	"art_id"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	"name"	TEXT NOT NULL,
	"band_id"	INTEGER NOT NULL,
	FOREIGN KEY("band_id") REFERENCES "band"("b_id")
);
CREATE TABLE IF NOT EXISTS "band" (
	"b_id"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	"band_name"	TEXT NOT NULL,
	"bt_id"	INTEGER,
	CONSTRAINT "band_FK" FOREIGN KEY("bt_id") REFERENCES "band_type"("bt_id") ON DELETE CASCADE ON UPDATE CASCADE
);
CREATE TABLE IF NOT EXISTS "company" (
	"c_id"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	"name"	TEXT NOT NULL,
	"address"	TEXT,
	"phone"	TEXT,
	"email"	TEXT,
	"status"	INTEGER NOT NULL DEFAULT 1
);
CREATE TABLE IF NOT EXISTS "artist_role" (
	"role_id"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	"name_role"	TEXT NOT NULL
);
CREATE TABLE IF NOT EXISTS "band_type" (
	"bt_id"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	"type_name"	TEXT NOT NULL,
	"descr"	TEXT
);
INSERT INTO "album" VALUES (NULL,464677360,15,4);
INSERT INTO "album" VALUES (NULL,464677360,40,4);
INSERT INTO "album" VALUES (NULL,464677360,44,4);
INSERT INTO "album" VALUES (NULL,464677360,49,4);
INSERT INTO "album" VALUES (NULL,464677360,51,4);
INSERT INTO "album" VALUES (NULL,464677360,58,4);
INSERT INTO "album" VALUES (NULL,464677360,59,4);
INSERT INTO "album" VALUES (NULL,464677360,65,4);
INSERT INTO "album" VALUES (NULL,464677360,68,4);
INSERT INTO "album" VALUES (NULL,464677360,77,4);
INSERT INTO "album" VALUES (NULL,369884514,151,3);
INSERT INTO "album" VALUES (NULL,369884514,152,3);
INSERT INTO "album" VALUES (NULL,369884514,153,3);
INSERT INTO "album" VALUES (NULL,369884514,154,3);
INSERT INTO "album" VALUES (NULL,369884514,156,7);
INSERT INTO "album" VALUES (NULL,369884514,160,7);
INSERT INTO "album" VALUES (NULL,369884514,162,8);
INSERT INTO "album" VALUES (NULL,369884514,163,8);
INSERT INTO "album" VALUES (NULL,369884514,164,8);
INSERT INTO "album" VALUES (NULL,369884514,165,8);
INSERT INTO "album" VALUES (NULL,524049170,101,4);
INSERT INTO "album" VALUES (NULL,524049170,102,1);
INSERT INTO "album" VALUES (NULL,524049170,103,7);
INSERT INTO "album" VALUES (NULL,524049170,104,5);
INSERT INTO "album" VALUES (NULL,524049170,105,3);
INSERT INTO "album" VALUES (NULL,524049170,106,5);
INSERT INTO "album" VALUES (NULL,524049170,107,2);
INSERT INTO "album" VALUES (NULL,524049170,108,2);
INSERT INTO "album" VALUES (NULL,524049170,109,1);
INSERT INTO "album" VALUES (NULL,524049170,110,4);
INSERT INTO "album" VALUES (NULL,524049170,111,5);
INSERT INTO "album" VALUES (NULL,524049170,112,2);
INSERT INTO "album" VALUES (NULL,524049170,113,7);
INSERT INTO "album" VALUES (NULL,524049170,114,3);
INSERT INTO "album" VALUES (NULL,524049170,115,4);
INSERT INTO "album" VALUES (NULL,524049170,116,3);
INSERT INTO "album" VALUES (NULL,524049170,117,2);
INSERT INTO "album" VALUES (NULL,524049170,118,7);
INSERT INTO "album" VALUES (NULL,524049170,119,7);
INSERT INTO "album" VALUES (NULL,524049170,120,1);
INSERT INTO "album" VALUES (NULL,524049170,121,8);
INSERT INTO "album" VALUES (NULL,524049170,122,8);
INSERT INTO "album" VALUES (NULL,524049170,123,8);
INSERT INTO "album" VALUES (NULL,660579451,51,4);
INSERT INTO "album" VALUES (NULL,660579451,54,6);
INSERT INTO "album" VALUES (NULL,660579451,58,4);
INSERT INTO "album" VALUES (NULL,660579451,59,4);
INSERT INTO "album" VALUES (NULL,660579451,60,1);
INSERT INTO "album" VALUES (NULL,660579451,63,1);
INSERT INTO "album" VALUES (NULL,660579451,64,1);
INSERT INTO "album" VALUES (NULL,660579451,65,4);
INSERT INTO "album" VALUES (NULL,660579451,66,5);
INSERT INTO "album" VALUES (NULL,660579451,67,2);
INSERT INTO "album" VALUES (NULL,660579451,68,4);
INSERT INTO "album" VALUES (NULL,660579451,69,5);
INSERT INTO "album" VALUES (NULL,660579451,70,2);
INSERT INTO "album" VALUES (NULL,660579451,72,5);
INSERT INTO "album" VALUES (NULL,660579451,73,5);
INSERT INTO "album" VALUES (NULL,867426320,52,7);
INSERT INTO "album" VALUES (NULL,867426320,53,3);
INSERT INTO "album" VALUES (NULL,867426320,55,7);
INSERT INTO "album" VALUES (NULL,867426320,56,3);
INSERT INTO "album" VALUES (NULL,867426320,57,3);
INSERT INTO "album" VALUES (NULL,867426320,61,3);
INSERT INTO "album" VALUES (NULL,867426320,62,7);
INSERT INTO "album" VALUES (NULL,867426320,71,7);
INSERT INTO "album" VALUES (NULL,867426320,78,3);
INSERT INTO "album" VALUES (NULL,867426320,81,3);
INSERT INTO "album" VALUES (NULL,867426320,84,7);
INSERT INTO "album" VALUES (NULL,867426320,85,3);
INSERT INTO "album" VALUES (NULL,867426320,89,7);
INSERT INTO "album" VALUES (NULL,867426320,92,3);
INSERT INTO "album" VALUES (NULL,867426320,93,7);
INSERT INTO "album" VALUES (NULL,271043443,31,3);
INSERT INTO "album" VALUES (NULL,271043443,73,5);
INSERT INTO "album" VALUES (NULL,271043443,6,6);
INSERT INTO "album" VALUES (NULL,271043443,22,7);
INSERT INTO "album" VALUES (NULL,271043443,102,1);
INSERT INTO "album" VALUES (NULL,271043443,121,8);
INSERT INTO "album" VALUES (NULL,271043443,127,8);
INSERT INTO "album" VALUES (NULL,867426321,2,3);
INSERT INTO "album" VALUES (NULL,867426321,3,3);
INSERT INTO "album" VALUES (NULL,867426321,5,3);
INSERT INTO "album" VALUES (NULL,867426321,7,5);
INSERT INTO "album" VALUES (NULL,867426321,4,1);
INSERT INTO "album" VALUES (NULL,867426322,12,7);
INSERT INTO "album" VALUES (NULL,867426322,18,6);
INSERT INTO "album" VALUES (NULL,867426322,45,1);
INSERT INTO "album" VALUES (NULL,867426322,123,8);
INSERT INTO "album" VALUES (NULL,867426322,140,8);
INSERT INTO "album" VALUES (NULL,867426323,11,7);
INSERT INTO "album" VALUES (NULL,867426323,19,7);
INSERT INTO "album" VALUES (NULL,867426323,24,7);
INSERT INTO "album" VALUES (NULL,867426323,31,3);
INSERT INTO "album" VALUES (NULL,867426323,33,6);
INSERT INTO "album" VALUES (NULL,867426321,34,2);
INSERT INTO "album" VALUES (NULL,867426321,118,7);
INSERT INTO "album" VALUES (NULL,867426321,149,8);
INSERT INTO "album" VALUES (NULL,867426321,96,7);
INSERT INTO "shop_ticket" VALUES (1,1,'2020-10-10',2.0,3);
INSERT INTO "shop_ticket" VALUES (2,1,'2020-10-11',1.0,10);
INSERT INTO "shop_ticket" VALUES (3,1,'2020-10-12',1.0,50);
INSERT INTO "shop_ticket" VALUES (4,2,'2020-10-20',3.0,3);
INSERT INTO "shop_ticket" VALUES (5,2,'2020-10-22',1.0,75);
INSERT INTO "shop_ticket" VALUES (6,4,'2020-05-15',2.0,25);
INSERT INTO "shop_ticket" VALUES (7,4,'2020-05-16',2.0,20);
INSERT INTO "shop_ticket" VALUES (8,4,'2020-05-17',4.0,3);
INSERT INTO "shop_ticket" VALUES (9,3,'2020-05-05',1.0,95);
INSERT INTO "shop_stock" VALUES (1,'2020-10-07',1,1.0,2.0,100);
INSERT INTO "shop_stock" VALUES (2,'2020-10-09',1,1.0,3.0,200);
INSERT INTO "shop_stock" VALUES (3,'2020-05-03',3,1.0,1.0,100);
INSERT INTO "shop_stock" VALUES (4,'2020-05-10',4,2.0,4.0,150);
INSERT INTO "album_release" VALUES (1,271043443,'2020-10-05',3);
INSERT INTO "album_release" VALUES (2,271043443,'2020-11-03',3);
INSERT INTO "album_release" VALUES (3,464677360,'2020-05-03',1);
INSERT INTO "album_release" VALUES (4,660579451,'2020-05-09',2);
INSERT INTO "album_matrix" VALUES (271043443,'Backup and restore',1);
INSERT INTO "album_matrix" VALUES (369884514,'?????????? ????????',2);
INSERT INTO "album_matrix" VALUES (464677360,'Engine and the other hand',1);
INSERT INTO "album_matrix" VALUES (524049170,'Ensemble of the most important',2);
INSERT INTO "album_matrix" VALUES (660579451,'Raised',2);
INSERT INTO "album_matrix" VALUES (867426320,'????????????????',2);
INSERT INTO "art_band_role" VALUES (6,1);
INSERT INTO "art_band_role" VALUES (8,3);
INSERT INTO "art_band_role" VALUES (9,6);
INSERT INTO "art_band_role" VALUES (23,2);
INSERT INTO "art_band_role" VALUES (24,3);
INSERT INTO "art_band_role" VALUES (25,3);
INSERT INTO "art_band_role" VALUES (26,3);
INSERT INTO "art_band_role" VALUES (27,3);
INSERT INTO "art_band_role" VALUES (28,4);
INSERT INTO "art_band_role" VALUES (29,4);
INSERT INTO "art_band_role" VALUES (30,4);
INSERT INTO "art_band_role" VALUES (31,1);
INSERT INTO "art_band_role" VALUES (32,6);
INSERT INTO "art_band_role" VALUES (33,6);
INSERT INTO "art_band_role" VALUES (34,7);
INSERT INTO "art_band_role" VALUES (35,5);
INSERT INTO "art_band_role" VALUES (36,3);
INSERT INTO "art_band_role" VALUES (37,7);
INSERT INTO "art_band_role" VALUES (38,6);
INSERT INTO "art_band_role" VALUES (39,1);
INSERT INTO "art_band_role" VALUES (40,5);
INSERT INTO "art_band_role" VALUES (41,3);
INSERT INTO "art_band_role" VALUES (42,2);
INSERT INTO "art_band_role" VALUES (43,3);
INSERT INTO "art_band_role" VALUES (44,1);
INSERT INTO "art_band_role" VALUES (45,5);
INSERT INTO "art_band_role" VALUES (46,6);
INSERT INTO "art_band_role" VALUES (47,7);
INSERT INTO "art_band_role" VALUES (48,6);
INSERT INTO "art_band_role" VALUES (49,2);
INSERT INTO "art_band_role" VALUES (50,3);
INSERT INTO "art_band_role" VALUES (54,3);
INSERT INTO "art_band_role" VALUES (55,4);
INSERT INTO "art_band_role" VALUES (56,5);
INSERT INTO "art_band_role" VALUES (57,6);
INSERT INTO "art_band_role" VALUES (58,7);
INSERT INTO "art_band_role" VALUES (59,6);
INSERT INTO "art_band_role" VALUES (60,6);
INSERT INTO "art_band_role" VALUES (61,1);
INSERT INTO "art_band_role" VALUES (62,3);
INSERT INTO "art_band_role" VALUES (63,4);
INSERT INTO "art_band_role" VALUES (64,2);
INSERT INTO "art_band_role" VALUES (65,3);
INSERT INTO "art_band_role" VALUES (66,1);
INSERT INTO "singles" VALUES (1,'Balls to the Wall',7,NULL);
INSERT INTO "singles" VALUES (2,'Desafinado',3,NULL);
INSERT INTO "singles" VALUES (3,'Garota De Ipanema',3,NULL);
INSERT INTO "singles" VALUES (4,'Samba De Uma Nota S?? (One Note Samba)',1,NULL);
INSERT INTO "singles" VALUES (5,'Por Causa De Voc??',3,NULL);
INSERT INTO "singles" VALUES (6,'Ligia',6,NULL);
INSERT INTO "singles" VALUES (7,'Fotografia',5,NULL);
INSERT INTO "singles" VALUES (8,'Dindi (Dindi)',1,NULL);
INSERT INTO "singles" VALUES (9,'Se Todos Fossem Iguais A Voc?? (Instrumental)',6,NULL);
INSERT INTO "singles" VALUES (10,'Falando De Amor',6,NULL);
INSERT INTO "singles" VALUES (11,'Angela',7,NULL);
INSERT INTO "singles" VALUES (12,'Corcovado (Quiet Nights Of Quiet Stars)',7,NULL);
INSERT INTO "singles" VALUES (13,'Outra Vez',5,NULL);
INSERT INTO "singles" VALUES (14,'O Boto (B??to)',7,NULL);
INSERT INTO "singles" VALUES (15,'Canta, Canta Mais',4,NULL);
INSERT INTO "singles" VALUES (16,'Intro/ Low Down',3,NULL);
INSERT INTO "singles" VALUES (17,'13 Years Of Grief',3,NULL);
INSERT INTO "singles" VALUES (18,'Stronger Than Death',6,NULL);
INSERT INTO "singles" VALUES (19,'All For You',7,NULL);
INSERT INTO "singles" VALUES (20,'Super Terrorizer',1,NULL);
INSERT INTO "singles" VALUES (21,'Phoney Smile Fake Hellos',6,NULL);
INSERT INTO "singles" VALUES (22,'Lost My Better Half',7,NULL);
INSERT INTO "singles" VALUES (23,'Bored To Tears',6,NULL);
INSERT INTO "singles" VALUES (24,'A.N.D.R.O.T.A.Z.',7,NULL);
INSERT INTO "singles" VALUES (25,'Born To Booze',1,NULL);
INSERT INTO "singles" VALUES (26,'World Of Trouble',1,NULL);
INSERT INTO "singles" VALUES (27,'No More Tears',3,NULL);
INSERT INTO "singles" VALUES (28,'The Begining... At Last',5,NULL);
INSERT INTO "singles" VALUES (29,'Heart Of Gold',5,NULL);
INSERT INTO "singles" VALUES (30,'Snowblind',6,NULL);
INSERT INTO "singles" VALUES (31,'Like A Bird',3,NULL);
INSERT INTO "singles" VALUES (32,'Blood In The Wall',2,NULL);
INSERT INTO "singles" VALUES (33,'The Beginning...At Last',6,NULL);
INSERT INTO "singles" VALUES (34,'Black Sabbath',2,NULL);
INSERT INTO "singles" VALUES (35,'The Wizard',2,NULL);
INSERT INTO "singles" VALUES (36,'Behind The Wall Of Sleep',7,NULL);
INSERT INTO "singles" VALUES (37,'N.I.B.',1,NULL);
INSERT INTO "singles" VALUES (38,'Evil Woman',1,NULL);
INSERT INTO "singles" VALUES (39,'Sleeping Village',6,NULL);
INSERT INTO "singles" VALUES (40,'Warning',4,NULL);
INSERT INTO "singles" VALUES (41,'Smoked Pork',5,NULL);
INSERT INTO "singles" VALUES (42,'Body Count''s In The House',3,NULL);
INSERT INTO "singles" VALUES (43,'Now Sports',5,NULL);
INSERT INTO "singles" VALUES (44,'Body Count',4,NULL);
INSERT INTO "singles" VALUES (45,'A Statistic',1,NULL);
INSERT INTO "singles" VALUES (46,'Bowels Of The Devil',2,NULL);
INSERT INTO "singles" VALUES (47,'The Real Problem',6,NULL);
INSERT INTO "singles" VALUES (48,'KKK Bitch',7,NULL);
INSERT INTO "singles" VALUES (49,'D Note',4,NULL);
INSERT INTO "singles" VALUES (50,'Voodoo',3,NULL);
INSERT INTO "singles" VALUES (51,'The Winner Loses',4,NULL);
INSERT INTO "singles" VALUES (52,'There Goes The Neighborhood',7,NULL);
INSERT INTO "singles" VALUES (53,'Oprah',3,NULL);
INSERT INTO "singles" VALUES (54,'Evil Dick',6,NULL);
INSERT INTO "singles" VALUES (55,'Body Count Anthem',7,NULL);
INSERT INTO "singles" VALUES (56,'Momma''s Gotta Die Tonight',3,NULL);
INSERT INTO "singles" VALUES (57,'Freedom Of Speech',3,NULL);
INSERT INTO "singles" VALUES (58,'Sozinho (Hitmakers Classic Mix)',4,NULL);
INSERT INTO "singles" VALUES (59,'Sozinho (Hitmakers Classic Radio Edit)',4,NULL);
INSERT INTO "singles" VALUES (60,'Sozinho (Ca??drum ''n'' Bass)',1,NULL);
INSERT INTO "singles" VALUES (61,'A Banda',3,NULL);
INSERT INTO "singles" VALUES (62,'Minha Historia',7,NULL);
INSERT INTO "singles" VALUES (63,'Com A????car E Com Afeto',1,NULL);
INSERT INTO "singles" VALUES (64,'Brejo Da Cruz',1,NULL);
INSERT INTO "singles" VALUES (65,'Meu Caro Amigo',4,NULL);
INSERT INTO "singles" VALUES (66,'Geni E O Zepelim',5,NULL);
INSERT INTO "singles" VALUES (67,'Trocando Em Mi??dos',2,NULL);
INSERT INTO "singles" VALUES (68,'Vai Trabalhar Vagabundo',4,NULL);
INSERT INTO "singles" VALUES (69,'Gota D''??gua',5,NULL);
INSERT INTO "singles" VALUES (70,'Constru????o / Deus Lhe Pague',2,NULL);
INSERT INTO "singles" VALUES (71,'Flor Do Futuro',7,NULL);
INSERT INTO "singles" VALUES (72,'Felicidade Urgente',5,NULL);
INSERT INTO "singles" VALUES (73,'Livre Pra Viver',5,NULL);
INSERT INTO "singles" VALUES (74,'Vai-Vai 2001',2,NULL);
INSERT INTO "singles" VALUES (75,'X-9 2001',1,NULL);
INSERT INTO "singles" VALUES (76,'Gavioes 2001',6,NULL);
INSERT INTO "singles" VALUES (77,'Nene 2001',4,NULL);
INSERT INTO "singles" VALUES (78,'Rosas De Ouro 2001',3,NULL);
INSERT INTO "singles" VALUES (79,'Mocidade Alegre 2001',6,NULL);
INSERT INTO "singles" VALUES (80,'Camisa Verde 2001',4,NULL);
INSERT INTO "singles" VALUES (81,'Midnight',3,NULL);
INSERT INTO "singles" VALUES (82,'Playtime',1,NULL);
INSERT INTO "singles" VALUES (83,'Surrender',4,NULL);
INSERT INTO "singles" VALUES (84,'Valentino''s',7,NULL);
INSERT INTO "singles" VALUES (85,'Believe',3,NULL);
INSERT INTO "singles" VALUES (86,'As We Sleep',4,NULL);
INSERT INTO "singles" VALUES (87,'When Evening Falls',1,NULL);
INSERT INTO "singles" VALUES (88,'J Squared',1,NULL);
INSERT INTO "singles" VALUES (89,'Best Thing',7,NULL);
INSERT INTO "singles" VALUES (90,'N??o D?? Mais Pra Segurar (Explode Cora????o)',1,NULL);
INSERT INTO "singles" VALUES (91,'Podres Poderes',2,NULL);
INSERT INTO "singles" VALUES (92,'Voce Nao Entende Nada - Cotidiano',3,NULL);
INSERT INTO "singles" VALUES (93,'O Estrangeiro',7,NULL);
INSERT INTO "singles" VALUES (94,'Menino Do Rio',3,NULL);
INSERT INTO "singles" VALUES (95,'Qualquer Coisa',1,NULL);
INSERT INTO "singles" VALUES (96,'Sampa',7,NULL);
INSERT INTO "singles" VALUES (97,'Queixa',3,NULL);
INSERT INTO "singles" VALUES (98,'O Leaozinho',5,NULL);
INSERT INTO "singles" VALUES (99,'Fora Da Ordem',7,NULL);
INSERT INTO "singles" VALUES (100,'Terra',7,NULL);
INSERT INTO "singles" VALUES (101,'Sombras Do Meu Destino',4,NULL);
INSERT INTO "singles" VALUES (102,'Do You Have Other Loves?',1,NULL);
INSERT INTO "singles" VALUES (103,'Agora Que O Dia Acordou',7,NULL);
INSERT INTO "singles" VALUES (104,'J??!!!',5,NULL);
INSERT INTO "singles" VALUES (105,'A Rua',3,NULL);
INSERT INTO "singles" VALUES (106,'Jeepers Creepers',5,NULL);
INSERT INTO "singles" VALUES (107,'Blue Rythm Fantasy',2,NULL);
INSERT INTO "singles" VALUES (108,'Drum Boogie',2,NULL);
INSERT INTO "singles" VALUES (109,'Let Me Off Uptown',1,NULL);
INSERT INTO "singles" VALUES (110,'Leave Us Leap',4,NULL);
INSERT INTO "singles" VALUES (111,'Don''t Take Your Love From Me',5,NULL);
INSERT INTO "singles" VALUES (112,'Midget',2,NULL);
INSERT INTO "singles" VALUES (113,'I''m Coming Virginia',7,NULL);
INSERT INTO "singles" VALUES (114,'Payin'' Them Dues Blues',3,NULL);
INSERT INTO "singles" VALUES (115,'Jungle Drums',4,NULL);
INSERT INTO "singles" VALUES (116,'Showcase',3,NULL);
INSERT INTO "singles" VALUES (117,'Swedish Schnapps',2,NULL);
INSERT INTO "singles" VALUES (118,'Samba Da B??n????o',7,NULL);
INSERT INTO "singles" VALUES (119,'Pot-Pourri N.?? 4',7,NULL);
INSERT INTO "singles" VALUES (120,'Onde Anda Voc??',1,NULL);
INSERT INTO "singles" VALUES (121,'Intro/ Low Down',8,NULL);
INSERT INTO "singles" VALUES (122,'13 Years Of Grief',8,NULL);
INSERT INTO "singles" VALUES (123,'Stronger Than Death',8,NULL);
INSERT INTO "singles" VALUES (124,'All For You',8,NULL);
INSERT INTO "singles" VALUES (125,'Super Terrorizer',8,NULL);
INSERT INTO "singles" VALUES (126,'Phoney Smile Fake Hellos',8,NULL);
INSERT INTO "singles" VALUES (127,'Lost My Better Half',8,NULL);
INSERT INTO "singles" VALUES (128,'Bored To Tears',8,NULL);
INSERT INTO "singles" VALUES (129,'A.N.D.R.O.T.A.Z.',8,NULL);
INSERT INTO "singles" VALUES (130,'Born To Booze',8,NULL);
INSERT INTO "singles" VALUES (131,'Behind The Wall Of Sleep',8,NULL);
INSERT INTO "singles" VALUES (132,'N.I.B.',8,NULL);
INSERT INTO "singles" VALUES (133,'Evil Woman',8,NULL);
INSERT INTO "singles" VALUES (134,'Sleeping Village',8,NULL);
INSERT INTO "singles" VALUES (135,'Warning',8,NULL);
INSERT INTO "singles" VALUES (136,'Smoked Pork',8,NULL);
INSERT INTO "singles" VALUES (137,'Body Count''s In The House',8,NULL);
INSERT INTO "singles" VALUES (138,'Now Sports',8,NULL);
INSERT INTO "singles" VALUES (139,'Body Count',8,NULL);
INSERT INTO "singles" VALUES (140,'A Statistic',8,NULL);
INSERT INTO "singles" VALUES (141,'Momma''s Gotta Die Tonight',8,NULL);
INSERT INTO "singles" VALUES (142,'Freedom Of Speech',8,NULL);
INSERT INTO "singles" VALUES (143,'Sozinho (Hitmakers Classic Mix)',8,NULL);
INSERT INTO "singles" VALUES (144,'Sozinho (Hitmakers Classic Radio Edit)',8,NULL);
INSERT INTO "singles" VALUES (145,'Sozinho (Ca??drum ''n'' Bass)',8,NULL);
INSERT INTO "singles" VALUES (146,'Carolina',8,NULL);
INSERT INTO "singles" VALUES (147,'Essa Mo??a Ta Diferente',8,NULL);
INSERT INTO "singles" VALUES (148,'Vai Passar',8,NULL);
INSERT INTO "singles" VALUES (149,'Samba De Orly',8,NULL);
INSERT INTO "singles" VALUES (150,'Bye, Bye Brasil',8,NULL);
INSERT INTO "singles" VALUES (151,'???????? ?? ?? ???????? ?????????? ???????????????????????? ?????? ???? ????????????',3,NULL);
INSERT INTO "singles" VALUES (152,'?? ?????????????????? ??????????',3,NULL);
INSERT INTO "singles" VALUES (153,'?????????????????? ?? ???????? ??????????????????',3,NULL);
INSERT INTO "singles" VALUES (154,'?????????????????? ?? ???????? ?????????? ?? ??????????',3,NULL);
INSERT INTO "singles" VALUES (155,'?????????? ???? ???????????? ???????????? ??????????',3,NULL);
INSERT INTO "singles" VALUES (156,'?????? ?????????? ?? ?????????????????? ??????????',7,NULL);
INSERT INTO "singles" VALUES (157,'?????????????????????? ?????????? ??????????',7,NULL);
INSERT INTO "singles" VALUES (158,'?????? ?? ???????????????? ???? ?? ??????????',7,NULL);
INSERT INTO "singles" VALUES (159,'?? ?????????????? ?? ???????? ??????????????',7,NULL);
INSERT INTO "singles" VALUES (160,'?????? ?????????? ???????? ???????? ?????? ???????????? ??????',7,NULL);
INSERT INTO "singles" VALUES (161,'?????? ???? ?????????????????? ???????? ??????????',8,NULL);
INSERT INTO "singles" VALUES (162,'?????? ???????? ???????????????????? ?? ??????????????',8,NULL);
INSERT INTO "singles" VALUES (163,'?????? ?????????? ???????????????????? ?? ??????????',8,NULL);
INSERT INTO "singles" VALUES (164,'?????? ?????????? ?????? ???? ???? ????????????????',8,NULL);
INSERT INTO "singles" VALUES (165,'?????????????????? ???????? ?????? ??????????????',8,NULL);
INSERT INTO "artist" VALUES (6,'?????????????????? ???????????? ??????????????????',3);
INSERT INTO "artist" VALUES (8,'?????????? ???????????? ????????????????',3);
INSERT INTO "artist" VALUES (9,'???????????????? ?????????? ??????????????????',3);
INSERT INTO "artist" VALUES (23,'???????????????? ???????????? ??????????????????',5);
INSERT INTO "artist" VALUES (24,'???????????????? ?????????? ????????????????',5);
INSERT INTO "artist" VALUES (25,'???????????? ???????? ??????????????????',5);
INSERT INTO "artist" VALUES (26,'???????????????? ?????????????? ??????????????????',5);
INSERT INTO "artist" VALUES (27,'???????????????? ???????????? ??????????????',5);
INSERT INTO "artist" VALUES (28,'?????????????? ???????????? ????????????????????',5);
INSERT INTO "artist" VALUES (29,'???????????? ???????????? ????????????????????',5);
INSERT INTO "artist" VALUES (30,'?????????????????? ???????????????? ????????????????????',7);
INSERT INTO "artist" VALUES (31,'?????????? ???????????? ??????????????',7);
INSERT INTO "artist" VALUES (32,'?????????????????? ?????????????? ????????????????????',7);
INSERT INTO "artist" VALUES (33,'???????????? ???????????? ??????????????????',7);
INSERT INTO "artist" VALUES (34,'?????????????? ?????????? ????????????????????',7);
INSERT INTO "artist" VALUES (35,'?????????????? ???????? ????????????????',7);
INSERT INTO "artist" VALUES (36,'?????????????? ????????????????',8);
INSERT INTO "artist" VALUES (37,'???????????????? ????????????',8);
INSERT INTO "artist" VALUES (38,'???????????????? ??????????????????',8);
INSERT INTO "artist" VALUES (39,'?????????????????? ????????',8);
INSERT INTO "artist" VALUES (40,'?????????????????? ??????????',8);
INSERT INTO "artist" VALUES (41,'???????????? ??????',8);
INSERT INTO "artist" VALUES (42,'???????????????? ????????????????',8);
INSERT INTO "artist" VALUES (43,'?????????????????? ??????????????????',8);
INSERT INTO "artist" VALUES (44,'?????????????? ??????????????????',8);
INSERT INTO "artist" VALUES (45,'?????????????? ??????????????????',8);
INSERT INTO "artist" VALUES (46,'?????????????? ????????????????',8);
INSERT INTO "artist" VALUES (47,'???????????????? ????????????',8);
INSERT INTO "artist" VALUES (48,'?????????????? ??????????????????',8);
INSERT INTO "artist" VALUES (49,'?????????????? ??????????????',8);
INSERT INTO "artist" VALUES (50,'???????????????? ????????????',8);
INSERT INTO "artist" VALUES (54,'Jason Lopez',1);
INSERT INTO "artist" VALUES (55,'Ricardo Miller',1);
INSERT INTO "artist" VALUES (56,'Edward Reynolds',1);
INSERT INTO "artist" VALUES (57,'Leah Jackson',2);
INSERT INTO "artist" VALUES (58,'Brittany Curry',2);
INSERT INTO "artist" VALUES (59,'Maria Russell',2);
INSERT INTO "artist" VALUES (60,'Ruth Moody',4);
INSERT INTO "artist" VALUES (61,'James Ford',4);
INSERT INTO "artist" VALUES (62,'Teresa Douglas',6);
INSERT INTO "artist" VALUES (63,'Lori Martin',6);
INSERT INTO "artist" VALUES (64,'Robert Smith',6);
INSERT INTO "artist" VALUES (65,'April Walker',6);
INSERT INTO "artist" VALUES (66,'Katie Davis',6);
INSERT INTO "band" VALUES (1,'Green Day',3);
INSERT INTO "band" VALUES (2,'Linkin park',3);
INSERT INTO "band" VALUES (3,'????????????',3);
INSERT INTO "band" VALUES (4,'Jazz Inside',2);
INSERT INTO "band" VALUES (5,'Perfect Me',2);
INSERT INTO "band" VALUES (6,'Hans Zimmer',5);
INSERT INTO "band" VALUES (7,'??????????????',2);
INSERT INTO "band" VALUES (8,'?????????????????????????? ?????????????? ??????',5);
INSERT INTO "company" VALUES (1,'Mirex','13053 E National Rd South Vienna, Ohio(OH), 45369','(937) 568-4239',NULL,1);
INSERT INTO "company" VALUES (2,'EMI','97 Keyes Rd Livingston, New Jersey(NJ), 07039','(240) 375-1288',NULL,1);
INSERT INTO "company" VALUES (3,'Sony Music Seller','Po Box 3694 Palmer, Alaska(AK), 99645','(201) 996-1427',NULL,0);
INSERT INTO "artist_role" VALUES (1,'????????????????????????');
INSERT INTO "artist_role" VALUES (2,'??????????????');
INSERT INTO "artist_role" VALUES (3,'????????????');
INSERT INTO "artist_role" VALUES (4,'??????????????');
INSERT INTO "artist_role" VALUES (5,'??????????????????');
INSERT INTO "artist_role" VALUES (6,'????????????');
INSERT INTO "artist_role" VALUES (7,'??????????????');
INSERT INTO "band_type" VALUES (1,'??????????????',NULL);
INSERT INTO "band_type" VALUES (2,'???????? ????????',NULL);
INSERT INTO "band_type" VALUES (3,'?????? ????????????',NULL);
INSERT INTO "band_type" VALUES (4,'??????????????',NULL);
INSERT INTO "band_type" VALUES (5,'?????????????????????????? ??????????????',NULL);
CREATE VIEW "vi_singles_albums" as
SELECT s.name as name, am.album_name as album_name, s.author as b_id, a.am_id as am_id, s.s_id as s_id  
FROM singles s left join album a on s.s_id = a.s_id
LEFT JOIN album_matrix am on a.am_id = am.am_id;
CREATE VIEW "vi_artist_role" as 
SELECT ar.name_role, a.name, b.b_id
FROM band b, artist a, art_band_role abr,  artist_role ar 
WHERE b.b_id = a.band_id
AND abr.art_id = a.art_id 
AND ar.role_id = abr.role_id;
COMMIT;
