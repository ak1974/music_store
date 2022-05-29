BEGIN TRANSACTION;
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
CREATE TABLE IF NOT EXISTS "album" (
	"a_id"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	"am_id"	INTEGER NOT NULL,
	"s_id"	INTEGER NOT NULL,
	"b_id"	INTEGER NOT NULL,
	FOREIGN KEY("s_id") REFERENCES "singles"("s_id"),
	FOREIGN KEY("b_id") REFERENCES "band"("b_id"),
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
INSERT INTO "band" VALUES (1,'Green Day',3);
INSERT INTO "band" VALUES (2,'Linkin park',3);
INSERT INTO "band" VALUES (3,'Сплинт',3);
INSERT INTO "band" VALUES (4,'Jazz Inside',2);
INSERT INTO "band" VALUES (5,'Perfect Me',2);
INSERT INTO "band" VALUES (6,'Hans Zimmer',5);
INSERT INTO "company" VALUES (1,'Mirex','13053 E National Rd South Vienna, Ohio(OH), 45369','(937) 568-4239',NULL,1);
INSERT INTO "company" VALUES (2,'EMI','97 Keyes Rd Livingston, New Jersey(NJ), 07039','(240) 375-1288',NULL,1);
INSERT INTO "company" VALUES (3,'Sony Music','Po Box 3694 Palmer, Alaska(AK), 99645','(201) 996-1427',NULL,1);
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
