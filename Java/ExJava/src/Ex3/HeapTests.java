package Ex3;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;



public class HeapTests {

	private float f1, f2, f3;
	private String s1, s2, s3;
	private int i1, i2, i3;

	private MinHeap<Float> HeapFloat;
	private MinHeap<String> HeapStr;
	private MinHeap<Integer> HeapInt;

	@Before
	public void initialize() {
		i1 = -122321;
		i2 = 0;
		i3 = 42093848;
		s1 = "";
		s2 = "A";
		s3 = "ABCD?abcd0123";
		f1 = (float) -2341.1234;
		f2 = (float) 0.0;
		f3 = (float) 12399282.1231;

		HeapFloat = new MinHeap<>();
		HeapStr = new MinHeap<>();
		HeapInt = new MinHeap<>();
	}

	@Test
	public void testIsEmpty_zeroEl() {
		assertTrue(HeapInt.isEmpty() && HeapFloat.isEmpty() && HeapStr.isEmpty());
	}

	@Test
	public void testIsEmpty_oneEl() {
		HeapInt.insert(i1);
		HeapFloat.insert(f1);
		HeapStr.insert(s1);
		assertFalse(HeapInt.isEmpty() && HeapFloat.isEmpty() && HeapStr.isEmpty());
	}

	@Test
	public void testSize_zeroEl() {
		assertEquals(0, HeapFloat.size());
		assertEquals(0, HeapStr.size());
		assertEquals(0, HeapInt.size());
	}

	@Test
	public void testSize_oneEl()  {
		HeapFloat.insert(f2);
		HeapInt.insert(i2);
		HeapStr.insert(s2);
		assertEquals(1, HeapFloat.size());
		assertEquals(1, HeapInt.size());
		assertEquals(1, HeapStr.size());
	}

	@Test
	public void testSize_twoEl()  {
		HeapInt.insert(i2);
		HeapInt.insert(i3);
		HeapFloat.insert(f2);
		HeapFloat.insert(f3);
		HeapStr.insert(s2);
		HeapStr.insert(s3);
		assertEquals(2, HeapFloat.size());
		assertEquals(2, HeapStr.size());
		assertEquals(2, HeapInt.size());
	}

	@Test
	public void testAdd_oneEl()  {
		HeapFloat.insert(f1);
		HeapInt.insert(i1);
		HeapStr.insert(s1);
		assertEquals(1, HeapFloat.size());
		assertEquals(1, HeapInt.size());
		assertEquals(1, HeapStr.size());
	}

	@Test
	public void testExtract_oneEl()  {
		HeapFloat.insert(f1);
		HeapFloat.insert(f2);
		HeapFloat.insert(f3);
		HeapInt.insert(i1);
		HeapInt.insert(i2);
		HeapInt.insert(i3);
		HeapStr.insert(s1);
		HeapStr.insert(s2);
		HeapStr.insert(s3);

		assertEquals(i1, (int) HeapInt.extract());
		assertEquals(f1, HeapFloat.extract(), 0.0);
		assertEquals(s1, HeapStr.extract());
	}


}
