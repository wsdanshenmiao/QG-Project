using UnityEngine;

namespace DSM
{

    public class Map
    {
        public long Width;
        public long Height;
        public Point[,] Points;
    }

    public class Point
    {
        public Vector2 Pos;
        public bool IsBarrier;
        public Point Parent;
        public float GCost;
        public float HCost;
        public float FCost;

        public Point(Vector2 pos, bool isBarrier = false, Point parent = null)
        {
            Pos = pos;
            Parent = parent;
            IsBarrier = isBarrier;
            GCost = 0;
            HCost = 0;
            FCost = 0;
        }

        public void ResetPointState()
        {
            GCost = 0;
            HCost = 0;
            FCost = 0;
            Parent = null;
        }

        #region Override Operator

        public static bool operator <(Point p1, Point p2)
        {
            return p1.FCost == p2.FCost ? p1.HCost < p2.HCost : p1.FCost < p2.FCost;
        }
        public static bool operator >(Point p1, Point p2)
        {
            return p1.FCost == p2.FCost ? p1.HCost > p2.HCost : p1.FCost > p2.FCost;
        }
        public static bool operator ==(Point p1, Point p2)
        {
            return p1?.Pos == p2?.Pos;
        }
        public static bool operator !=(Point p1, Point p2)
        {
            return !(p1 == p2);
        }

        public override bool Equals(object obj)
        {
            if (obj == null || obj.GetType() != this.GetType()) return false;
            return this == (Point)obj;
        }

        public override int GetHashCode()
        {
            return Pos.GetHashCode();
        }
        #endregion
    }

}
