/** * Created by manzarkazi on 1/13/16. */
class IndexValue {
  private static int indexValue(int[] a, int start, int end) {
      System.out.println("checking from: "+start+" to: "+end);
    if (end < start) { return -1; } 
    int mid = (start + end) / 2; 
    if (a[mid] == mid) { 
      System.out.println("value in the array @ index "+mid+" is the same as index ");
      return mid; 
    } else if (mid < a[mid]) { 
      return indexValue(a, start, mid - 1);
    } else { 
      return indexValue(a, mid + 1, end); 
    } 
  } 

  public static int indexMatchingValue(int[] a) {
    if (a == null || a.length == 0) { return -1; } 
    return indexValue(a, 0, a.length - 1); 
  } 

  public static void main(String arg[]) {
    int[] a = new int[]{-1, 0, 1, 2, 3, 5}; 
    System.out.println(indexMatchingValue(a)); 
    a = new int[]{0}; 
    System.out.println(indexMatchingValue(a)); 
    a = new int[]{-1, 1, 2, 3}; 
    System.out.println(indexMatchingValue(a)); 
  } 
}