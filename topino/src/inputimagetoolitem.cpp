#include "include/inputimagetoolitem.h"

InputImageToolItem::InputImageToolItem(int newitemid, QGraphicsItem* parent) :
    TopinoGraphicsItem(newitemid, parent) {
    setFlags(QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);

    setAcceptHoverEvents(true);

    emptybox = QBrush(QColor(42, 42, 42), Qt::SolidPattern);
    borderpen = QPen(QColor(125, 125, 125));
    borderpen.setWidth(2);
    borderpen.setStyle(Qt::DashLine);
    borderpen.setDashPattern({5, 5});
    borderpen.setDashOffset(2.5);
}

InputImageToolItem::~InputImageToolItem() {
}

QRectF InputImageToolItem::boundingRect() const {
    return rect;
}

void InputImageToolItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);

    /* Fill the whole tool with a background color */
    painter->fillRect(rect, emptybox);

    /* Zero image will draw a little box */
    if (pixmap.isNull()) {
        painter->setBrush(emptybox);
        painter->setPen(borderpen);
        painter->drawRect(rect);

        painter->drawText(rect.adjusted(20, 20, -20, -20), Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextWordWrap,
                          tr("No image loaded. Use File➔Import Image... to import and evaluate an image."));
    } else {
        painter->drawPixmap(rect, pixmap, pixmap.rect());
    }
}

QPainterPath InputImageToolItem::shape() const {
    /* Basically just add the rectangle as shape */
    QPainterPath path;
    path.addRect(rect);

    return path;
}

TopinoGraphicsItem::itemtype InputImageToolItem::getItemType() const {
    return TopinoGraphicsItem::itemtype::image;
}

void InputImageToolItem::updateScale() {
    /* There is no need to scale the image at all since all other tools are scale
     * relative to the image; therefore, this function is empty. */
}

void InputImageToolItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    TopinoGraphicsItem::mousePressEvent(event);
}

void InputImageToolItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    TopinoGraphicsItem::mouseMoveEvent(event);
}

void InputImageToolItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    TopinoGraphicsItem::mouseReleaseEvent(event);
}

void InputImageToolItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event) {
    TopinoGraphicsItem::hoverMoveEvent(event);
}

QString InputImageToolItem::toString() const {
    return QString("Image: %1 × %2 Px²").arg(pixmap.width()).arg(pixmap.height());
}

void InputImageToolItem::calculateRect() {
    /* Make sure that the tool has some dimensions, even if there is no image; also
     * add a 10% border to each side of the image (i.e. 2 * 10% = 20%), so that other
     * tools can actually be placed on or a little bit outside of the image */
    if (pixmap.isNull()) {
        rect = QRectF(0, 0, 480, 480);
    } else {
        rect = pixmap.rect();
    }
}

QPixmap InputImageToolItem::getPixmap() const {
    return pixmap;
}

void InputImageToolItem::setPixmap(const QPixmap value) {
    pixmap = value;
    calculateRect();
}
