#include "cryptoprice.h"
#include "remoteimage.h"

#include "styles/style_chat_helpers.h"

namespace Bettergram {

CryptoPrice::CryptoPrice(const QUrl &url,
						 const QUrl &iconUrl,
						 const QString &name,
						 const QString &shortName,
						 int rank,
						 QObject *parent) :
	QObject(parent),
	_url(url),
	_icon(new RemoteImage(iconUrl, st::pricesPanTableImageSize, st::pricesPanTableImageSize)),
	_name(name),
	_shortName(shortName),
	_rank(rank)
{
	connect(_icon.data(), &RemoteImage::imageChanged, this, &CryptoPrice::iconChanged);
}

CryptoPrice::CryptoPrice(const QUrl &url,
						 const QUrl &iconUrl,
						 const QString &name,
						 const QString &shortName,
						 int rank,
						 double currentPrice,
						 double changeFor24Hours,
						 bool isCurrentPriceGrown,
						 QObject *parent) :
	QObject(parent),
	_url(url),
	_icon(new RemoteImage(iconUrl, st::pricesPanTableImageSize, st::pricesPanTableImageSize)),
	_name(name),
	_shortName(shortName),
	_rank(rank),
	_currentPrice(currentPrice),
	_changeFor24Hours(changeFor24Hours),
	_isCurrentPriceGrown(isCurrentPriceGrown),
	_isChangeFor24HoursGrown(_changeFor24Hours >= 0.0)
{
	connect(_icon.data(), &RemoteImage::imageChanged, this, &CryptoPrice::iconChanged);
}

CryptoPrice::CryptoPrice(const CryptoPrice &price, QObject *parent) :
	QObject(parent),
	_url(price._url),
	_icon(price._icon),
	_name(price._name),
	_shortName(price._shortName),
	_rank(price._rank),
	_currentPrice(price._currentPrice),
	_changeFor24Hours(price._changeFor24Hours),
	_isCurrentPriceGrown(price._isCurrentPriceGrown),
	_isChangeFor24HoursGrown(price._isChangeFor24HoursGrown)
{
	connect(_icon.data(), &RemoteImage::imageChanged, this, &CryptoPrice::iconChanged);
}

CryptoPrice &CryptoPrice::operator=(const CryptoPrice &price)
{
	setUrl(price._url);
	setIcon(price._icon);
	setName(price._name);
	setShortName(price._shortName);
	setRank(price._rank);
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

void CryptoPrice::setIcon(const QSharedPointer<RemoteImage> &icon)
{
	_icon = icon;
}

const QUrl &CryptoPrice::iconUrl() const
{
	return _icon->link();
}

const QPixmap &CryptoPrice::icon() const
{
	return _icon->image();
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

int CryptoPrice::rank() const
{
	return _rank;
}

void CryptoPrice::setRank(int rank)
{
	if (_rank != rank) {
		_rank = rank;
		emit rankChanged();
	}
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
