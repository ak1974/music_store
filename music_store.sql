BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "art_band_role" (
	"art_id"	INTEGER NOT NULL,
	"role_id"	INTEGER NOT NULL,
	CONSTRAINT "art_role_FK" FOREIGN KEY("role_id") REFERENCES "artist_role"("role_id") ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT "art_band_role_FK" FOREIGN KEY("art_id") REFERENCES "artist"("art_id") ON DELETE CASCADE ON UPDATE CASCADE
);
CREATE TABLE IF NOT EXISTS "artist" (
	"art_id"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	"name"	TEXT NOT NULL,
	"band_id"	INTEGER
);
CREATE TABLE IF NOT EXISTS "band" (
	"b_id"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	"band_name"	TEXT NOT NULL,
	"bt_id"	INTEGER NOT NULL
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
INSERT INTO "band" VALUES (1,'Green Day',3);
INSERT INTO "band" VALUES (2,'Linkin park',3);
INSERT INTO "band" VALUES (3,'Сплинт',3);
INSERT INTO "band" VALUES (4,'Jazz Inside',2);
INSERT INTO "band" VALUES (5,'Perfect Me',2);
INSERT INTO "band" VALUES (6,'Hans Zimmer',5);
INSERT INTO "artist_role" VALUES (1,'Руководитель');
INSERT INTO "artist_role" VALUES (2,'Дирижер');
INSERT INTO "artist_role" VALUES (3,'Басист');
INSERT INTO "artist_role" VALUES (4,'Ударник');
INSERT INTO "artist_role" VALUES (5,'Клавишник');
INSERT INTO "artist_role" VALUES (6,'Солист');
INSERT INTO "artist_role" VALUES (7,'Скрипач');
INSERT INTO "band_type" VALUES (1,'Квартет',NULL);
INSERT INTO "band_type" VALUES (2,'Джаз банд',NULL);
INSERT INTO "band_type" VALUES (3,'Рок группа',NULL);
INSERT INTO "band_type" VALUES (4,'Квинтет',NULL);
INSERT INTO "band_type" VALUES (5,'Симфонический оркестр',NULL);
COMMIT;
