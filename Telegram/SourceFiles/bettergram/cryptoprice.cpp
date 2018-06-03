/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/

#include "cryptoprice.h"

namespace Bettergram {

CryptoPrice::CryptoPrice(const QUrl &url,
						 const QUrl &iconUrl,
						 const QString &name,
						 const QString &shortName,
						 QObject *parent) :
	QObject(parent),
	_url(url),
	_iconUrl(iconUrl),
	_name(name),
	_shortName(shortName)
{
}

CryptoPrice::CryptoPrice(const QUrl &url,
						 const QUrl &iconUrl,
						 const QString &name,
						 const QString &shortName,
						 double currentPrice,
						 double changeFor24Hours,
						 bool isCurrentPriceGrown,
						 QObject *parent) :
	QObject(parent),
	_url(url),
	_iconUrl(iconUrl),
	_name(name),
	_shortName(shortName),
	_currentPrice(currentPrice),
	_changeFor24Hours(changeFor24Hours),
	_isCurrentPriceGrown(isCurrentPriceGrown),
	_isChangeFor24HoursGrown(_changeFor24Hours >= 0.0)
{
}

CryptoPrice::CryptoPrice(const CryptoPrice &price, QObject *parent) :
	QObject(parent),
	_url(price._url),
	_iconUrl(price._iconUrl),
	_name(price._name),
	_shortName(price._shortName),
	_currentPrice(price._currentPrice),
	_changeFor24Hours(price._changeFor24Hours),
	_isCurrentPriceGrown(price._isCurrentPriceGrown),
	_isChangeFor24HoursGrown(price._isChangeFor24HoursGrown)
{
}

CryptoPrice &CryptoPrice::operator=(const CryptoPrice &price)
{
	setUrl(price._url);
	setIconUrl(price._iconUrl);
	setName(price._name);
	setShortName(price._shortName);
	setCurrentPrice(price._currentPrice);
	setChangeFor24Hours(price._changeFor24Hours);
	setIsCurrentPriceGrown(price._isCurrentPriceGrown);

	return *this;
}

const QUrl &CryptoPrice::url() const
{
	return _url;
}

void CryptoPrice::setUrl(const QUrl &url)
{
	_url = url;
}

const QUrl &CryptoPrice::iconUrl() const
{
	return _iconUrl;
}

void CryptoPrice::setIconUrl(const QUrl &iconUrl)
{
	_iconUrl = iconUrl;
}

const QString &CryptoPrice::name() const
{
	return _name;
}

void CryptoPrice::setName(const QString &name)
{
	_name = name;
}

const QString &CryptoPrice::shortName() const
{
	return _shortName;
}

void CryptoPrice::setShortName(const QString &shortName)
{
	_shortName = shortName;
}

double CryptoPrice::currentPrice() const
{
	return _currentPrice;
}

QString CryptoPrice::currentPriceString() const
{
	if (_currentPrice < 1.0) {
		return QString("$%1").arg(_currentPrice, 0, 'f', 4);
	} else {
		return QString("$%1").arg(_currentPrice, 0, 'f', 2);
	}
}

void CryptoPrice::setCurrentPrice(double currentPrice)
{
	if (_currentPrice != currentPrice) {
		_currentPrice = currentPrice;
		emit currentPriceChanged();
	}
}

double CryptoPrice::changeFor24Hours() const
{
	return _changeFor24Hours;
}

QString CryptoPrice::changeFor24HoursString() const
{
	return QString("%1%").arg(_changeFor24Hours, 0, 'f', 2);
}

void CryptoPrice::setChangeFor24Hours(double changeFor24Hours)
{
	if (_changeFor24Hours != changeFor24Hours) {
		_changeFor24Hours = changeFor24Hours;

		setIsChangeFor24HoursGrown(_changeFor24Hours >= 0.0);
		emit changeFor24HoursChanged();
	}
}

bool CryptoPrice::isCurrentPriceGrown() const
{
	return _isCurrentPriceGrown;
}

void CryptoPrice::setIsCurrentPriceGrown(bool isCurrentPriceGrown)
{
	if (_isCurrentPriceGrown != isCurrentPriceGrown) {
		_isCurrentPriceGrown = isCurrentPriceGrown;
		emit currentPriceChanged();
	}
}

bool CryptoPrice::isChangeFor24HoursGrown() const
{
	return _isChangeFor24HoursGrown;
}

void CryptoPrice::setIsChangeFor24HoursGrown(bool isChangeFor24HoursGrown)
{
	if (_isChangeFor24HoursGrown != isChangeFor24HoursGrown) {
		_isChangeFor24HoursGrown = isChangeFor24HoursGrown;
		emit isChangeFor24HoursGrownChanged();
	}
}

void CryptoPrice::updateData(const CryptoPrice &price)
{
	setCurrentPrice(price.currentPrice());
	setChangeFor24Hours(price.changeFor24Hours());
	setIsCurrentPriceGrown(price.isCurrentPriceGrown());
}

} // namespace Bettergrams