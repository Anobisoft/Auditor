
DROP USER 'localusr'@'localhost';
CREATE USER 'localusr'@'localhost' IDENTIFIED BY 'usrpassword';
GRANT DELETE, INSERT, SELECT, UPDATE ON inspectordb.* TO 'localusr'@'localhost';

DROP USER 'lnetusr'@'192.168.1.0/255.255.255.0';
CREATE USER 'lnetusr'@'192.168.1.0/255.255.255.0' IDENTIFIED BY 'usrpassword';
GRANT DELETE, INSERT, SELECT, UPDATE ON inspectordb.* TO 'lnetusr'@'192.168.1.0/255.255.255.0';

DROP USER 'rmtusr'@'%';
CREATE USER 'rmtusr'@'%' IDENTIFIED BY 'rmtusrpassword';
GRANT DELETE, INSERT, SELECT, UPDATE ON inspectordb.* TO 'rmtusr'@'%';

