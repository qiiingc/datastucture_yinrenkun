// 栈的抽象基类定义
template <class T>
class StackWalk
{
public:
	virtual void Push(const T &x) = 0;	// 新元素x入栈
	virtual bool Pop(T &x) = 0;			// 栈顶元素出栈，由x返回
	virtual bool getTop(T &x) = 0;		// 读取栈顶函数，由x返回
	virtual bool IsEmpty() const = 0;	// 判断栈空否
	virtual bool IsFull() const = 0;	// 判断栈满否
	virtual int getSize() const = 0;	// 返回当前栈的大小
};