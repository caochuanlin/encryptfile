bool EncryptFileFromLocal( const QString& strOriginalFilePath,const QString& strEncryptedFilePath,bool bDeleteOriginalFile /*= true*/ )
{
	QFile original_file(strOriginalFilePath);
	QFile encrypted_file(strEncryptedFilePath);

	if (!original_file.open(QIODevice::ReadOnly))
	{
		return false;
	}

	if (!encrypted_file.open(QIODevice::WriteOnly))
	{
		return false;
	}

	QByteArray encrypted_data = original_file.readAll().toBase64();

	QTextStream writer(&encrypted_file); 
	writer<<encrypted_data;

	original_file.close();
	encrypted_file.close();

	if (bDeleteOriginalFile)
	{
		QFile::remove(strOriginalFilePath);
	}

	return true;
}

bool DecryptFileToLocal( const QString& strEncryptedFilePath,const QString& strDestFilePath,bool bDeleteEncryptedFile /*= true*/ )
{
	QFile dest_file(strDestFilePath);
	if (!dest_file.open(QIODevice::WriteOnly))
	{
		return false;
	}

	QFile encrypted_file(strEncryptedFilePath);
	if (!encrypted_file.open(QIODevice::ReadOnly))
	{
		return false;
	}

	QByteArray byte_array = QByteArray::fromBase64(encrypted_file.readAll());

	QTextStream writer(&dest_file); 
	writer<<byte_array;

	dest_file.close();
	encrypted_file.close();

	if (bDeleteEncryptedFile)
	{
		QFile::remove(strEncryptedFilePath);
	}

	return true;
}

bool EncryptFileFromData( const QByteArray& byte_data,const QString& strEncryptedFilePath )
{
	QFile encrypted_file(strEncryptedFilePath);
	if (!encrypted_file.open(QIODevice::WriteOnly))
	{
		return false;
	}

	QByteArray encrypted_data = byte_data.toBase64();

	QTextStream writer(&encrypted_file); 
	writer<<encrypted_data;

	encrypted_file.close();

	return true;
}

bool DecryptFileToData( const QString& strEncryptedFilePath,QByteArray& byte_data )
{
	QFile file(strEncryptedFilePath);
	if (!file.open(QIODevice::ReadOnly))
	{
		return false;
	}

	byte_data = QByteArray::fromBase64(file.readAll());

	file.close();

	return true;
}